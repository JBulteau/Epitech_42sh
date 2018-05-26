/*
** EPITECH PROJECT, 2017
** magic_quotes.c
** File description:
** MAgic quotes functions
*/

#include <stddef.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

char *get_magic(shell_t *shell, char *comm)
{
//	char *magic = NULL;
	shell_t *dup = dup_shell(shell);

	dup->input = comm;
	run_that(dup);
	free_aliases(dup->aliases, 1);
	free_history(dup->history);
	for (int i = 0; dup->vars[i]; i++)
		free_var(dup->vars[i]);
	free(dup->vars);
	free_array((void **)dup->env);
	free(comm);
	free(dup);
	return (strdup("Ceci arrive julo"));
}

history_t *dup_history(history_t *node)
{
	history_t *new = NULL;

	if (node == NULL)
		return (NULL);
	new = malloc(sizeof(history_t) * 1);
	if (new == NULL)
		return (NULL);
	new->data = strdup(node->data);
	new->next = dup_history(node->next);
	return (new);
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

var_t **dup_vars(var_t **arr)
{
	int len = array_len((void **)arr);
	var_t **new = malloc(sizeof(var_t *) * len);

	if (new == NULL)
		return (NULL);
	new[len - 1] = NULL;
	for (int i = 0; arr[i]; i++) {
		new[i] = malloc(sizeof(var_t) * 1);
		if (new[i] == NULL)
			return (NULL);
		new[i]->name = strdup(arr[i]->name);
		new[i]->type = arr[i]->type;
		if (new[i]->type == STR)
			new[i]->data.content = strdup(arr[i]->data.content);
		else if (new[i]->type == NBR)
			new[i]->data.value = arr[i]->data.value;
		else
			new[i]->data.content = NULL;
	}
	return (new);
}