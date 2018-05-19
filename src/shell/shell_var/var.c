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
	var_t *var = malloc(sizeof (var_t) * 1);

	var->type = NO_TYPE;
	var->data.value = 0;
	var->name = NULL;
	
	if (var == NULL)
		return (NULL);
	return (var);
}

void free_var(var_t *var) {
	if (var->type == STR)
		free(var->data.content);
	free(var->name);
	free(var);
}

var_t **init_var_arr(void)
{
	var_t **arr = malloc(sizeof (var_t *) * 1);

	if (arr == NULL)
		return (NULL);
	arr[0] = NULL;
	return (arr);
}

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

void disp_vars(var_t **arr)
{
	if (arr == NULL)
		return ((void)puts("ARRAY IS NULL"));
	if (arr[0] == NULL)
		return ((void)puts("NO VARS SET"));
	for (int i = 0; arr[i]; i++) {
		printf("{\n\t\tTYPE: ");
		switch (arr[i]->type) {
		case NONE:
			puts("NONE");
			break;
		case STR:
			printf("STR\n\t\tcontent:%s\n", arr[i]->data.value);
			break;
		case NBR:
			printf("INT\n\t\tvalue:%i\n", arr[i]->data.value);
			break;
		default:
			break;
		}
		puts("}");
	}
}

var_t **try_vars(void)
{
	var_t **arr = init_var_arr();
	if(arr == NULL)
		return (NULL);
	disp_vars(arr);
	arr = set_var(arr, "var_name1", "content");
	arr = set_var(arr, "var_name2", "+42");
	disp_vars(arr);
	return (arr);
}