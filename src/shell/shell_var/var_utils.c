/*
** EPITECH PROJECT, 2017
** var_utils.c
** File description:
** Var utils functions
*/

#include <string.h>
#include "minishell.h"
#include "my.h"

int find_var(var_t **arr, char *name)
{
	if (arr == NULL)
		return (ERROR_RETURN);
	for (int i = 0; arr[i] != NULL; i++)
		if (!strcmp(arr[i]->name, name))
			return (i);
	return (ERROR_RETURN);
}

type_t get_type(char *content)
{
	if (content == NULL)
		return (NO_TYPE);
	if (is_num(content) == 0)
		return (NBR);
	return (STR);
}