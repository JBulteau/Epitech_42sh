/*
** EPITECH PROJECT, 2017
** alias.c
** File description:
** Alias builtins
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

int disp_help(void)
{
	puts("Usage: alias [rm] [name[=alias]]");
	return (EXIT_SUCCESS);
}

int disp_aliases(alias_t *node)
{
	if (node == NULL) {
		puts("No alias set");
		return (SUCCESS_RETURN);
	}
	for (alias_t *current = node; current != NULL; current = \
current->nav[NEXT])
		printf("%s=%s\n", current->name, current->alias);
	return (SUCCESS_RETURN);
}

static int disp_help_unset(void)
{
	puts("Usage: alias <name>");
	return (EXIT_SUCCESS);
}

int ptr_alias(comm_t *comm, shell_t *shell)
{
	if (comm->argv[1] == NULL)
		return (disp_aliases(shell->aliases));
	if (!strcmp(comm->argv[1], "--help") || !strcmp(comm->argv[1], "-h"))
		return (disp_help());
	if (!strcmp(comm->argv[1], "rm") || !strcmp(comm->argv[1], "delete")) {
		if (rm_alias(shell, comm->argv[2], comm) == ERROR_RETURN)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if ((add_alias(comm->argv, shell) == ERROR_RETURN) || (update_aliases(shell, comm, 0, 1) == ERROR_RETURN))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int ptr_unalias(comm_t *comm, shell_t *shell)
{
	if (!strcmp(comm->argv[1], "--help") || !strcmp(comm->argv[1], "-h"))
		return (disp_help_unset());
	if (rm_alias(shell, comm->argv[1], comm) == ERROR_RETURN)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}