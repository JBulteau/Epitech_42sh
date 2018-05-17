/*
** EPITECH PROJECT, 2017
** alias.c
** File description:
** Builtins alias
*/

#include <string.h>
#include <stdio.h>
#include "minishell.h"

int disp_help(void)
{
	puts("Usage: alias [rm] [name[=alias]]");
	return (0);
}

int replace_alias(alias_t *node, comm_t *comm)
{
	for (alias_t *curr = node; node != NULL; node = node->nav[NEXT]) {
		if (!strcmp(comm->argv[0], curr->name)) {
			free(comm->argv[0]);
			comm->argv[0] = strdup(curr->alias);
		}
		if ((!strcmp(comm->argv[0], curr->name)) && (comm->argv[0] == \
NULL))
			return (-1);
	}
	return (0);
}

void rm_one_alias(char *alias, alias_t *current, shell_t *shell)
{
	if (!strcmp(alias, current->name)) {
		if (current->nav[PREV] == NULL)
			shell->aliases = current->nav[NEXT];
		free_aliases(current, 0);
	}
}

int rm_alias(shell_t *shell, char **av)
{
	if (av[2] == NULL) {
		puts("Please specify an alias to remove");
		return (1);
	}
	if (shell->aliases == NULL) {
		return (0);
	}
	for (alias_t *current = shell->aliases; current != NULL; current = \
current->nav[NEXT]) {
		for (int i = 2; av[i] != NULL; i++)
			rm_one_alias(av[i], current, shell);
	}
	return (0);
}

int ptr_alias(comm_t *comm, shell_t *shell)
{
	if (comm->argv[1] == NULL)
		return (disp_aliases(shell->aliases));
	if (!strcmp(comm->argv[1], "--help") || !strcmp(comm->argv[1], "-h"))
		return (disp_help());
	if (!strcmp(comm->argv[1], "rm") || !strcmp(comm->argv[1], "delete"))
		return (rm_alias(shell, comm->argv));
	return (add_alias(comm->argv, shell));
}