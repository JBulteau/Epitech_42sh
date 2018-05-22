/*
** EPITECH PROJECT, 2017
** alias_struc.c
** File description:
** Alias structure functions
*/

#include <stdio.h>
#include <unistd.h>
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

char *concat_args(char **args)
{
	char *res = NULL;
	int add_space = 2;
	int res_len = 0;

	for (int i = 0; args[i] != NULL; i++) {
		if (args[i + 1] == NULL)
			add_space = 1;
		if (res == NULL)
			res = malloc(strlen(args[i]) + add_space);
		else
			res = realloc(res, res_len + strlen(args[i]) + add_space);
		if (res == NULL)
			return (NULL);
		strcpy(res + res_len, args[i]);
		res_len = strlen(res);
		if (add_space == 2)
			res[res_len++] = ' ';
	}
	return (res);
}

int add_alias(char **args, shell_t *shell)
{
	alias_t *last = NULL;
	char *alias = NULL;

	if (args == NULL || args[0] == NULL || args[1] == NULL || args[2] == NULL)
		return (ERROR_RETURN);
	alias = concat_args(args + 2);
	if (alias == NULL)
		return (ERROR_RETURN);
	if (shell->aliases == NULL) {
		shell->aliases = create_alias(args[1], alias, NULL);
		if (shell->aliases == NULL)
			return (ERROR_RETURN);
		return (SUCCESS_RETURN);
	}
	for (last = shell->aliases; last->nav[NEXT] != NULL; last = last->nav[NEXT]);
	last->nav[NEXT] = create_alias(args[1], alias, last);
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