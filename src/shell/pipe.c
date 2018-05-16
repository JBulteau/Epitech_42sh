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
	//fprintf(stderr, "PIPE initialized: READ: %i WRITE: %i\n", pipe_->fd[READ], pipe_->fd[WRITE]);
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
	pid_t father = getpid();
	pid_t last_pid;
	int status = 0;

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
	} while (last_pid != pid && last_pid != father && last_pid != -1);
	if (last_pid != father && last_pid != -1)
		remove_last_pid();
	return (WEXITSTATUS(status));
}

void debug_pid(char *s)
{
	fprintf(stderr, "|%i|%s\n", getpid(), s);
}

int init_redir_pipe(comm_t *comm)
{
	if (comm->pipe[IN]) {
	//	fprintf(stderr, "|%i| |%s %s|REDIRECT STDIN FROM pipe[READ]: %i\n", getpid(), comm->argv[0], comm->argv[1], comm->pipe[IN]->fd[READ]);
		if (dup2(comm->pipe[IN]->fd[READ], STDIN_FILENO) == -1) {
			perror("dup2");
			return (-1);
		}
	}
	if (comm->pipe[OUT]) {
	//	fprintf(stderr, "|%i| |%s %s| REDIRECT STDOUT to pipe[WRITE]: %i\n", getpid(), comm->argv[0], comm->argv[1], comm->pipe[OUT]->fd[WRITE]);
		if (dup2(comm->pipe[OUT]->fd[WRITE], STDOUT_FILENO) == -1) {
			perror("dup2");
			return (-1);
		}
		close(comm->pipe[OUT]->fd[READ]);
	}
}

int run_not_last(shell_t *shell, comm_t *curr)
{
	pid_t child_pid;

	if ((child_pid = fork()) == -1)
		return (ERROR_RETURN);
	if (child_pid == 0) {
		init_redir_pipe(curr);
		if (is_builtin(curr->argv[0]) != -1)
			exit(exec_bi(curr, shell));
		else
			exec_bin(curr, shell->env);
	}
	if (curr->pipe[OUT])
		close(curr->pipe[OUT]->fd[WRITE]);
	close_in(curr);
	return (0);
}

void close_in(comm_t *curr)
{
	if (curr->pipe[IN]) {
		close(curr->pipe[IN]->fd[READ]);
		close(curr->pipe[IN]->fd[WRITE]);
	}
}

int run_last_pipeline(shell_t *shell, comm_t *curr)
{
	pid_t child_pid;
	int return_c = 0;

	if (is_builtin(curr->argv[0]) != -1) {
		init_redir_pipe(curr);		
		return_c = exec_bi(curr, shell);
	} else {
		if ((child_pid = fork()) == -1)
			return (ERROR_RETURN);
		else if (child_pid == 0) {
			init_redir_pipe(curr);
			exec_bin(curr, shell->env);
		}
		return_c = wait_for_it(child_pid);
	}
	close_in(curr);
	return (return_c);
}

int run_pipeline(shell_t *shell, comm_t *comm)
{
	int return_c = 0;

	if ((shell == NULL) || (comm == NULL))
		return (-ERROR_CODE);
	for (comm_t *curr = comm; curr; curr = (curr->pipe[OUT] && curr->pipe[OUT]->output) ? curr->pipe[OUT]->output : NULL) {
		if (curr->pipe[OUT] == NULL) {
			return_c = run_last_pipeline(shell, curr);
		} else {
			return_c = run_not_last(shell, curr);
		}
	}
	return (return_c);
}