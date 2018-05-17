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

alias_t *create_alias(char *name, char*alias, alias_t *prev)
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

int disp_aliases(alias_t *node)
{
	if (node == NULL) {
		puts("No alias set");
		return (0);
	}
	for (alias_t *current = node; current != NULL; current = \
current->nav[NEXT])
		printf("%s=%s\n", current->name, current->alias);
	return (0);
}

int add_alias(char **args, shell_t *shell)
{
	alias_t *last = NULL;
	char **split = NULL;
	int i = 1;
	if (shell->aliases == NULL) {
		split = strwordarr(args[i++], "=");
		puts(split[0]);
		if (split[1] == NULL) {
			free_array((void **)split);
			return (1);
		}
		puts(split[1]);
		shell->aliases = create_alias(split[0], split[1], NULL);
	}
	last = shell->aliases;
	for (; last->nav[NEXT] != NULL; last = last->nav[NEXT]);
	for (; args[i] != NULL; last = last->nav[NEXT]) {
		split = strwordarr(args[i++], "=");
		last->nav[NEXT] = create_alias(split[0], split[1], last);
	}
	return (0);
}

void free_aliases(alias_t *alias, int free_next)
{
	if (alias == NULL)
		return;
	free(alias->name);
	free(alias->alias);
	if (free_next)
		free_aliases(alias->nav[NEXT], 1);
	else {
		if (alias->nav[PREV] != NULL)
			alias->nav[PREV]->nav[NEXT] = alias->nav[NEXT];
		if (alias->nav[NEXT] != NULL)
			alias->nav[NEXT]->nav[PREV] = alias->nav[PREV];
	}
	free(alias);
}