/*
** EPITECH PROJECT, 2017
** alias.c
** File description:
** Builtins alias
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"
#include <string.h>

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
	for (alias_t *current = node; current != NULL; current = current->nav[NEXT])
		printf("%s=%s\n", current->name, current->alias);
	return (0);
}

int disp_help(void)
{
	puts("Usage: alias [rm] [name[=alias]]");
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
	alias_t prev;
	alias_t next;

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

int replace_alias(alias_t *node, comm_t *comm)
{
	for (alias_t *curr = node; node != NULL; node = node->nav[NEXT]) {
		if (!strcmp(comm->argv[0], node->name)) {
			free(comm->argv[0]);
			comm->argv[0] = strdup(node->alias);
			if (comm->argv[0] == NULL)
				return (-1);
		}
	}
	return (0);
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
	for (alias_t *current = shell->aliases; current != NULL; current = current->nav[NEXT]) {
		for (int i = 2; av[i] != NULL; i++) {
			if (!strcmp(av[i], current->name)) {
				if (current->nav[PREV] == NULL)
					shell->aliases = current->nav[NEXT];
				free_aliases(current, 0);
			}
		}
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