/*
** EPITECH PROJECT, 2017
** exec.c
** File description:
** Execution fnc
*/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "minishell.h"
#include "tokens.h"
#include "my.h"

int exec_start(comm_t *comm)
{
	for (int i = 0; i < 4; i++)
		if (comm->red[i] && tokens[i].fnc_exec(comm) == -1)
			return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int exec_end(comm_t *comm)
{
	for (int i = 0; i < 4; i++)
		if (comm->red[i] && (tokens[i].end_exec(comm) == ERROR_RETURN))
			return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int run_that_comm(shell_t *shell, comm_t *comm)
{
	int pipeline;

	if (comm->parenthesis != NULL)
		pipeline = exec_loop(shell, comm->parenthesis);
	else
		pipeline = run_pipeline(shell, comm);
	if (pipeline == ERROR_RETURN)
			return (ERROR_RETURN);
	if ((comm->separator == OR && shell->return_value != 0) || (comm->separator == THEN && shell->return_value == 0))
		pipeline = run_that_comm(shell, comm->next);
	return (pipeline);
}

int exec_loop(shell_t *shell, comm_t **comm_arr)
{
	int pipeline = 0;

	for (int i = 0; comm_arr[i] != NULL; i++) {
		pipeline = run_that_comm(shell, comm_arr[i]);
		if (pipeline == ERROR_RETURN)
			return (ERROR_RETURN);
	}
	return (pipeline);
}

int exec_bin(comm_t *comm, char **env, shell_t *shell)
{
	int is_local = (!strncmp(comm->argv[0], "./", 2)) || \
(index_of(comm->argv[0], '/') != -1);
	char **path = NULL;
	char *filepath = NULL;

	if (is_local == 1 && !search_local(comm->argv[0])) {
		return (run_bin(comm, strdup(comm->argv[0]), env, shell));
	} else if (is_local == 0) {
		if ((path = get_path(env, shell->vars)) == NULL) {
			disp_rights(comm->argv[0], -1, 0);
			clean_exit(shell, 1);
		}
		filepath = search_path(path, comm->argv[0]);
		free_array((void **) path);
		if (filepath == NULL)
			clean_exit(shell, 1);
		return (run_bin(comm, filepath, env, shell));
	}
	clean_exit(shell, 1);
	return (ERROR_RETURN);
}
