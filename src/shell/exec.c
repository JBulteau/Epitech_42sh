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
#include "my.h"
#include "jarvis.h"

#include <sys/stat.h>
#include <fcntl.h>

int exec_loop(shell_t *shell)
{
	int return_code = 0;

	for (int i = 0; shell->comm[i] != NULL; i++) {
		exec_start(shell->comm[i]);
		return_code = exec_comm(shell->comm[i], &(shell->env), shell->pwd);
		exec_end(shell->comm[i]);
		if (return_code == -1)
			return (1);
		if (return_code == ERROR_CODE)
			return (ERROR_CODE);
	}
	return (return_code);
}

int exec(comm_t *comm, char *path, char **env, int jarvis)
{
	int status = 0;
	int child_pid = fork();

	if (child_pid == 0)
		if (execve(path, comm->argv, env) == -1) {
			disp_wrong_arch(comm->argv[0], errno);
			return (-1);
		}
	waitpid(child_pid, &status, WUNTRACED);
	display_signal(status);
	if (comm->argv[1] != NULL && jarvis != 1 && status != 0) {
		status = jarvis_corrector(comm, &env, 3, path);
		return (status);
	}
	free(path);
	return (status == 256 ? 1 : status);
}

int exec_comm(comm_t *comm, char ***env, char pwd[2][PATH_MAX])
{
	int is_local = (!my_strcmp(comm->argv[0], "./", 2)) || \
(index_of(comm->argv[0], '/') != -1);
	char **path = NULL;
	char *filepath = NULL;

	if (is_builtin(comm->argv[0]) >= 0)
		return (exec_bi(comm, env, pwd));
	if (is_local == 1 && !search_local(comm->argv[0])) {
		return (exec(comm, my_strndup(comm->argv[0], 0), *env, 0));
	} else if (is_local == 0) {
		if ((path = get_path(*env)) == NULL) {
			disp_rights(comm->argv[0], -1, 0);
			return (1);
		}
		filepath = search_path(path, comm->argv[0]);
		free_array((void **) path);
		if (filepath == NULL) {
			//call jarvis non local if he is = 0 return 0 else le return 1 en dessous
			return (1);
		}
		return (exec(comm, filepath, *env, 0));
	}
	return (1);
}