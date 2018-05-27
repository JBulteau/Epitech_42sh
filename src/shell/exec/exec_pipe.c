/*
** EPITECH PROJECT, 2017
** exec_pipe.c
** File description:
** Pipe execution functions
*/

#include <string.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"

int run_not_last(shell_t *shell, comm_t *curr)
{
	pid_t child_pid;

	if ((child_pid = fork()) == -1)
		return (ERROR_RETURN);
	if (child_pid == 0) {
		exec_start(curr);
		init_redir_pipe(curr);
		if (is_builtin(curr->argv[0]) != -1)
			clean_exit(shell, exec_bi(curr, shell));
		else
			exec_bin(curr, shell->env, shell);
	}
	if (add_pid_jobs(child_pid) == -1)
		return (ERROR_RETURN);
	close(curr->pipe[OUT]->fd[WRITE]);
	close_in(curr);
	exec_end(curr);
	return (SUCCESS_RETURN);
}

int run_and_fork(shell_t *shell, comm_t *curr)
{
	pid_t child_pid;

	if ((child_pid = fork()) == -1)
		return (ERROR_RETURN);
	else if (child_pid == 0) {
		exec_start(curr);
		init_redir_pipe(curr);
		exec_bin(curr, shell->env, shell);
	}
	if (add_pid_jobs(child_pid) == -1)
		return (ERROR_RETURN);
	shell->return_value = wait_for_it(child_pid);
	return (SUCCESS_RETURN);
}

int run_last_pipeline(shell_t *shell, comm_t *curr)
{
	int bi_return = 0;

	if (is_builtin(curr->argv[0]) != -1) {
		exec_start(curr);
		init_redir_pipe(curr);
		if (find_node_job()->pid_job[0] == 0)
			remove_node(0);
		if ((bi_return = exec_bi(curr, shell)) == -ERROR_CODE) {
			return (-ERROR_CODE);
		} else
			shell->return_value = bi_return;
	} else if (run_and_fork(shell, curr) == ERROR_RETURN)
		return (ERROR_RETURN);
	exec_end(curr);
	close_in(curr);
	return (SUCCESS_RETURN);
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
		if ((curr->separator == OR && shell->return_value != 0) || \
(curr->separator == THEN && shell->return_value == 0))
		return_c = run_that_comm(shell, curr->next);
	}
	return (return_c);
}