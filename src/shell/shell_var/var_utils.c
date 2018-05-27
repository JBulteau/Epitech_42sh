/*
** EPITECH PROJECT, 2017
** var_utils.c
** File description:
** Var utils functions
*/

#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

int find_var(var_t **arr, char *name)
{
	if (arr == NULL || name == NULL)
		return (ERROR_RETURN);
	for (int i = 0; arr[i] != NULL; i++) {
		if (!strcmp(arr[i]->name, name))
			return (i);
	}
	return (ERROR_RETURN);
}

char *get_var_str(var_t *var)
{
	char buff[256];

	if (var->type == STR)
		return (strdup(var->data.content));
	if (var->type == NBR) {
		sprintf(buff, "%i", var->data.value);
		return (strdup(buff));
	}
	return (NULL);
}

char *get_var(char **env, var_t **vars, char *name)
{
	int id = find_var(vars, name);
	int len;
	char *res = NULL;

	if (name == NULL)
		return (NULL);
	if (id != -1) {
		res = get_var_str(vars[id]);
		return (res);
	}
	len = strlen(name);
	for (id = 0; env && env[id] != NULL; id++)
		if (strncmp(env[id], name, len) == 0)
			res = strdup(env[id] + len + 1);
	return (res);
}

type_t get_type(char *content)
{
	if (content == NULL)
		return (NO_TYPE);
	if (content[0] && is_num(content) == 0)
		return (NBR);
	return (STR);
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