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
	if (arr == NULL)
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

	if (id != -1) {
		printf("Shell var found at id %i\n", id);
		res = get_var_str(vars[id]);
		return (res);
	}
	len = strlen(name);
	for (id = 0; env[id] != NULL; id++)
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