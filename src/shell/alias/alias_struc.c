/*
** EPITECH PROJECT, 2017
** alias_struc.c
** File description:
** Alias structure functions
*/

#include <stdio.h>
#include <string.h>
#include "my.h"
#include "minishell.h"

alias_t *create_alias(char *name, char *alias, alias_t *prev)
{
	alias_t *new = malloc(sizeof(alias_t) * 1);

	if (new == NULL)
		return (NULL);
	new->alias = strdup(alias);
	new->name = strdup(name);
	new->nav[PREV] = prev;
	new->nav[NEXT] = NULL;
	return (new);
}

int add_alias(char **args, shell_t *shell)
{
	alias_t *last = NULL;
	char **split = NULL;
	int i = 1;

	if (shell->aliases == NULL) {
		split = strwordarr(args[i++], "=");
		if (split[1] == NULL) {
			free_array((void **)split);
			return (ERROR_RETURN);
		}
		shell->aliases = create_alias(split[0], split[1], NULL);
	}
	last = shell->aliases;
	for (; last->nav[NEXT] != NULL; last = last->nav[NEXT]);
	for (; args[i] != NULL; last = last->nav[NEXT]) {
		split = strwordarr(args[i++], "=");
		last->nav[NEXT] = create_alias(split[0], split[1], last);
	}
	free_array((void *)split);
	return (SUCCESS_RETURN);
}

void free_aliases(alias_t *alias, int free_next)
{
	alias_t *nav[2];

	if (alias == NULL)
		return;
	nav[PREV] = alias->nav[PREV];
	nav[NEXT] = alias->nav[NEXT];
	free(alias->name);
	free(alias->alias);
	if (free_next)
		free_aliases(alias->nav[NEXT], 1);
	else {
		if (nav[PREV] != NULL)
			nav[PREV]->nav[NEXT] = nav[NEXT];
		if (nav[NEXT] != NULL)
			nav[NEXT]->nav[PREV] = nav[PREV];
	}
	free(alias);
}