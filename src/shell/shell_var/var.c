/*
** EPITECH PROJECT, 2017
** var.c
** File description:
** Shell var struct fncs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"

var_t *init_var(void)
{
	var_t *var = malloc(sizeof(var_t) * 1);

	var->type = NO_TYPE;
	var->data.value = 0;
	var->name = NULL;
	if (var == NULL)
		return (NULL);
	return (var);
}

void free_var(var_t *var)
{
	if (var->type == STR)
		free(var->data.content);
	free(var->name);
	free(var);
}

var_t **init_var_arr(void)
{
	var_t **arr = malloc(sizeof(var_t *) * 1);

	if (arr == NULL)
		return (NULL);
	arr[0] = NULL;
	return (arr);
}

void disp_vars(var_t **arr)
{
	if (arr == NULL)
		return ((void)puts("ARRAY IS NULL"));
	if (arr[0] == NULL)
		return ((void)puts("NO VARS SET"));
	for (int i = 0; arr[i]; i++) {
		printf("{\n\t\tTYPE: ");
		switch (arr[i]->type) {
		case NOTHING:
			puts("NONE");
			break;
		case STR:
			printf("STR\n\t\tcontent:%s\n", arr[i]->data.content);
			break;
		case NBR:
			printf("INT\n\t\tvalue:%i\n", arr[i]->data.value);
			break;
		}
		puts("}");
	}
}

var_t **try_vars(void)
{
	var_t **arr = init_var_arr();
	if (arr == NULL)
		return (NULL);
	disp_vars(arr);
	arr = set_var(arr, "var_name1", "content");
	arr = set_var(arr, "var_name2", "+42");
	disp_vars(arr);
	return (arr);
}
