/*
** EPITECH PROJECT, 2017
** pipe.c
** File description:
** Pipe functions
*/

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "minishell.h"
#include "my.h"

pipe_t *init_pipe(comm_t *in, comm_t *out)
{
	pipe_t *pipe_ = malloc(sizeof(pipe_t) * 1);

	if ((pipe_ == NULL) || (in == NULL) || (out == NULL))
		return (NULL);
	pipe_->input = in;
	pipe_->output = out;
	if (pipe(pipe_->fd) == -1)
		return (NULL);
	return (pipe_);
}

void destroy_pipe(pipe_t *pipe)
{
	close(pipe->fd[0]);
	close(pipe->fd[1]);
	free(pipe);
}

int wait_for_it(pid_t pid)
{
	pid_t last_pid;
	int status;

	do {
		last_pid = wait(&status);
		if (!WIFSIGNALED(status))
			continue;
		if (WTERMSIG(status) == 8)
			my_puterror("Floating exception");
		else
			my_puterror(strsignal(WTERMSIG(status)));
		if (WCOREDUMP(status))
			my_puterror(" (core dumped)");
		my_puterror("\n");
	} while (last_pid != pid);
	return (status);
}

int redirect_pipe_at_exec(comm_t *curr)
{
	if (curr->pipe[IN]) {
		if (dup2(curr->pipe[IN]->fd[READ], STDIN_FILENO) == -1)
			return (ERROR_RETURN);
		close(curr->pipe[IN]->fd[WRITE]);
	}
	if (curr->pipe[OUT]) {
		if (dup2(curr->pipe[OUT]->fd[WRITE], STDOUT_FILENO) == -1)
			return (ERROR_RETURN);
		close(curr->pipe[OUT]->fd[READ]);
	}
	return (SUCCESS_RETURN);
}

void debug_pid(char *s)
{
	fprintf(stderr, "|%i|%s\n", getpid(), s);
}


int run_pipeline(shell_t *shell, comm_t *comm)
{
	//TODO AJOUTER LES REDIRECTIONS FDP
	int return_c = 0;
	pid_t child_pid;

	if ((shell == NULL) || (comm == NULL))
		return (ERROR_RETURN);
	for (comm_t *curr = comm; curr; curr = (curr->pipe[OUT] && curr->pipe[OUT]->output) ? curr->pipe[OUT]->output : NULL) {
		if (curr->pipe[OUT] == NULL) {
			if (is_builtin(curr->argv[0]) != -1)
				//TODO REDIRECT fd --> STDIN
				return_c = exec_bi(curr, shell);
				//TODO close fd + rd STDIN to STDIN
			else {
				if ((child_pid = fork()) == -1)
					return (ERROR_RETURN);
				else if (child_pid == 0) {
					redirect_pipe_at_exec(curr);
					exec_bin(curr, shell->env);
				}
				if (curr->pipe[IN]) {
					close(curr->pipe[IN]->fd[WRITE]);
					close(curr->pipe[IN]->fd[READ]);
				}
				wait_for_it(child_pid);
			}
		} else {
			if ((child_pid = fork()) == -1)
				return (ERROR_RETURN);
			if (child_pid == 0) {
				redirect_pipe_at_exec(curr);
				if (is_builtin(curr->argv[0]) != -1) {
					return_c = exec_bi(curr, shell);
					exit(return_c);
				} else
					exec_bin(curr, shell->env);
			}
			if (curr->pipe[OUT]) {
				//close(curr->pipe[OUT]->fd[READ]);
				close(curr->pipe[OUT]->fd[WRITE]);
			}
		}
	}
	//TODO FERMER LES REDIR FDP
	return (0);
}