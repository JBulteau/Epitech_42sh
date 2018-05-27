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
	puts("Usage:\n\t\talias <name> <alias...>\n\t\talias rm <name>");
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
		printf("%s\t%s\n", current->name, current->alias);
	return (SUCCESS_RETURN);
}

static int disp_help_unset(void)
{
	puts("Usage: unalias <name>");
	return (EXIT_SUCCESS);
}

int ptr_alias(comm_t *comm, shell_t *shell)
{
	if (comm->argv[1] == NULL)
		return (disp_aliases(shell->aliases));
	if (!strcmp(comm->argv[1], "--help") || !strcmp(comm->argv[1], "-h"))
		return (disp_help());
	if (!strcmp(comm->argv[1], "rm") || !strcmp(comm->argv[1], "delete")) {
		if (rm_alias(shell, comm->argv[2]) == ERROR_RETURN)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (add_alias(comm->argv, shell) == ERROR_RETURN)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int ptr_unalias(comm_t *comm, shell_t *shell)
{
	if (!comm->argv[1] || !strcmp(comm->argv[1], "--help") \
	|| !strcmp(comm->argv[1], "-h"))
		return (disp_help_unset());
	for (int i = 1; comm->argv[i] != NULL; i++)
		if (rm_alias(shell, comm->argv[i]) == ERROR_RETURN)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}