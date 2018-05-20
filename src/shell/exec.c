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
	for (int i = 0; i < 4; i++) {
		if (comm->red[i] && tokens[i].fnc_exec(comm) == -1) {
			return (ERROR_RETURN);
		}
	}
	return (SUCCESS_RETURN);
}

int exec_end(comm_t *comm)
{
	for (int i = 0; i < 4; i++)
		if (comm->red[i] && (tokens[i].end_exec(comm) == ERROR_RETURN))
			return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int exec_pl_separators(shell_t *shell, comm_t *comm)
{
	if (run_pipeline(shell, comm) == ERROR_RETURN)
		return (ERROR_RETURN);
	if ((((comm->separator == THEN) && (shell->return_value == 0)) || ((comm->separator == OR) && (shell->return_value != 0))) && comm->next) {
		return (exec_pl_separators(shell, comm->next));
	} else if (comm->separator != NOTHING) {
		while (comm && comm->separator != NOTHING)
			comm = comm->next;
	}
}

int exec_loop(shell_t *shell)
{
	//for (int i = 0; shell->comm[i]; i++)
	//	debug_comm(shell->comm[i]);
	for (int i =0; shell->comm[i]; i++)
		exec_pl_separators(shell, shell->comm[i]);
	return (shell->return_value);
}

int exec_bin(comm_t *comm, char **env)
{
	int is_local = (!strncmp(comm->argv[0], "./", 2)) || \
(index_of(comm->argv[0], '/') != -1);
	char **path = NULL;
	char *filepath = NULL;

	if (is_local == 1 && !search_local(comm->argv[0])) {
		return (run_bin(comm, strdup(comm->argv[0]), env));
	} else if (is_local == 0) {
		if ((path = get_path(env)) == NULL) {
			disp_rights(comm->argv[0], -1, 0);
			exit(1);
		}
		filepath = search_path(path, comm->argv[0]);
		free_array((void **) path);
		if (filepath == NULL)
			exit(1);
		return (run_bin(comm, filepath, env));
	}
	exit(1);
}

int run_bin(comm_t *comm, char *path, char **env)
{
	if (execve(path, comm->argv, env) == -1) {
		disp_wrong_arch(comm->argv[0], errno);
	}
	exit(1);
}
