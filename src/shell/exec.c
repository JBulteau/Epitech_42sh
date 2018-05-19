/*
** EPITECH PROJECT, 2017
** exec.c
** File description:
** Execution fnc
*/

#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "tokens.h"
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

int exec_loop(shell_t *shell)
{
	int return_code = 0;

	for (int i = 0; shell->comm[i] != NULL; i++) {
		exec_start(shell->comm[i]);
		return_code = run_pipeline(shell, shell->comm[i]);
		exec_end(shell->comm[i]);
		if (return_code == -1)
			return (1);
		if (return_code == -ERROR_CODE)
			return (-ERROR_CODE);
	}
	return (return_code);
}

int exec_bin(comm_t *comm, char **env)
{
	int is_local = (!my_strcmp(comm->argv[0], "./", 2)) || \
(index_of(comm->argv[0], '/') != -1);
	char **path = NULL;
	char *filepath = NULL;

	if (is_local == 1 && !search_local(comm->argv[0])) {
		return (run_bin(comm, my_strndup(comm->argv[0], 0), env));
	} else if (is_local == 0) {
		if ((path = get_path(env)) == NULL) {
			disp_rights(comm->argv[0], -1, 0);
			exit (1);
		}
		filepath = search_path(path, comm->argv[0]);
		free_array((void **) path);
		if (filepath == NULL)
			exit (1);
		return (run_bin(comm, filepath, env));
	}
	exit (1);
}

int run_bin(comm_t *comm, char *path, char **env)
{
	if (execve(path, comm->argv, env) == -1) {
		disp_wrong_arch(comm->argv[0], errno);
	}
	exit (1);
}