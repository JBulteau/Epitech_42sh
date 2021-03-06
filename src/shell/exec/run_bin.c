/*
** EPITECH PROJECT, 2017
** run_bin.c
** File description:
** Function that execve
*/

#include <errno.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"

int run_that(shell_t *shell)
{
	int return_code = 0;

	if ((shell->comm = parsing(shell)) == NULL) {
		shell->return_value = 1;
		return (ERROR_CODE);
	}
	return_code = exec_loop(shell, shell->comm);
	if (shell->return_value && isatty(STDIN_FILENO) && (call_jarvis_rerun\
(shell) == ERROR_RETURN))
		return (ERROR_RETURN);
	if (shell->comm != NULL)
		free_comms(shell->comm);
	return (return_code);
}

int run_bin(comm_t *comm, char *path, char **env, shell_t *shell)
{
	if (execve(path, comm->argv, env) == -1)
		disp_wrong_arch(comm->argv[0], errno);
	clean_exit(shell, 1);
	return (ERROR_RETURN);
}