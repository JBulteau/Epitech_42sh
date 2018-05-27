/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** printenv builtin fncs
*/

#include "my.h"
#include "minishell.h"
#include <string.h>
#include <stdio.h>

int find_variable(char **env, char *variable)
{
	int j;

	for (int i = 0; env[i]; i++) {
		for (j = 0; env[i][j] != '='; j++);
		if (!strncmp(variable, env[i], j) \
		&& (int)strlen(variable) == j) {
			puts(&env[i][j + 1]);
			return (SUCCESS_RETURN);
		}
	}
	return (1);
}

int ptr_printenv(comm_t *comm, shell_t *shell)
{
	if (shell == NULL || shell->env == NULL)
		return (1);
	if (comm->argv[1] != NULL) {
		if (comm->argv[2] != NULL) {
			puts("printenv: Too many arguments.");
			return (1);
		} else {
			return (find_variable(shell->env, comm->argv[1]));
		}
	} else {
		for (int i = 0; shell->env[i]; i++)
			puts(shell->env[i]);
	}
	return (SUCCESS_RETURN);
}