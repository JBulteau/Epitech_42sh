/*
** EPITECH PROJECT, 2017
** exec_pipe.c
** File description:
** Pipe execution functions
*/

#include <unistd.h>
#include "my.h"
#include "minishell.h"

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
	if (add_pid_jobs(child_pid) == -1)
		return (ERROR_RETURN);
	if (curr->pipe[OUT])
		close(curr->pipe[OUT]->fd[WRITE]);
	close_in(curr);
	return (0);
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
		if (add_pid_jobs(child_pid) == -1)
			return (ERROR_RETURN);
		return_c = wait_for_it(child_pid);
	}
	close_in(curr);
	return (return_c);
}

int run_pipeline(shell_t *shell, comm_t *comm)
{
	int return_c = 0;

	if ((shell == NULL) || (comm == NULL) || new_node() == NULL)
		return (-ERROR_CODE);
	for (comm_t *curr = comm; curr; curr = (curr->pipe[OUT] && curr->pipe\
[OUT]->output) ? curr->pipe[OUT]->output : NULL) {
		if (curr->pipe[OUT] == NULL) {
			return_c = run_last_pipeline(shell, curr);
		} else {
			return_c = run_not_last(shell, curr);
		}
	}
	return (return_c);
}