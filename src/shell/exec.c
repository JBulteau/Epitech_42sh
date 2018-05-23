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
	int pipeline = 0;

	for (int i =0; shell->comm[i] != NULL; i++) {
		if ((pipeline = run_pipeline(shell, shell->comm[i])) == ERROR_RETURN)
			return (ERROR_RETURN);
		if (!(((shell->comm[i]->separator == THEN) && (shell->return_v\
alue == 0)) || ((shell->comm[i]->separator == OR) && (shell->return_value != 0\
)))) {
			while (shell->comm[i]->separator != NONE)
				i++;
		}
	}
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
		if ((path = get_path(env)) == NULL) {
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

int run_bin(comm_t *comm, char *path, char **env, shell_t *shell)
{
	if (execve(path, comm->argv, env) == -1)
		disp_wrong_arch(comm->argv[0], errno);
	clean_exit(shell, 1);
	return (ERROR_RETURN);
}
