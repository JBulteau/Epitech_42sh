/*
** EPITECH PROJECT, 2017
** var_edition.c
** File description:
** Functions that are used to edit vars
*/

#include <string.h>
#include "minishell.h"
#include "my.h"

int edit_var(var_t *var, char *content, char *name)
{
	if (name != var->name) {
		free(var->name);
		var->name = strdup(name);
	}
	if (var->type == STR)
		free(var->data.content);
	var->type = get_type(content);
	if (var->type == STR)
		var->data.content = strdup(content);
	if (var->type == NBR)
		var->data.value = atoi(content);
	return (SUCCESS_RETURN);
}

var_t **set_var(var_t **arr, char *name, char *content)
{
	int id = find_var(arr, name);
	int len;

	if (id == -1) {
		len = array_len((void *)arr) - 1;
		arr = realloc(arr, sizeof(var_t *) * (len + 2));
		arr[len] = init_var();
		arr[len + 1] = NULL;
		if (arr[len] == NULL)
			return (NULL);
		id = len;
	}
	if (edit_var(arr[id], content, name) == ERROR_RETURN)
		return (NULL);
	return (arr);
}