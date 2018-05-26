/*
** EPITECH PROJECT, 2017
** alias_comm.c
** File description:
** Alias fnc that edits comm argv
*/

#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"

int rm_alias(shell_t *shell, char *alias)
{
	alias_t *tmp = NULL;

	if (alias == NULL) {
		puts("Please specify an alias to remove");
		return (EXIT_FAILURE);
	}
	if (shell->aliases == NULL)
		return (EXIT_SUCCESS);
	for (alias_t *current = shell->aliases; current != NULL; UNUSED((tmp \
= current) && (current = current->nav[NEXT]))) {
		if (!strcmp(current->name, alias) && (shell->aliases == curren\
t)) {
			shell->aliases = current->nav[NEXT];
			free_aliases(current, 0);
			current = shell->aliases;
		} else if (!strcmp(current->name, alias)) {
			free_aliases(current, 0);
			current = tmp;
		}
	}
	return (EXIT_SUCCESS);
}

alias_t *dup_aliases(alias_t *alias)
{
	alias_t *new = NULL;

	if (alias == NULL)
		return (NULL);
	new = malloc(sizeof(alias_t) * 1);
	if (new == NULL)
		return (NULL);
	new->name = strdup(alias->name);
	if (new->name == NULL)
		return (NULL);
	new->alias = strdup(alias->alias);
	if (new->alias == NULL)
		return (NULL);
	new->nav[PREV] = alias->nav[PREV];
	new->nav[NEXT] = dup_aliases(alias->nav[NEXT]);
	return (new);
}