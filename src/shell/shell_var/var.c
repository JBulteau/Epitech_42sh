/*
** EPITECH PROJECT, 2017
** var.c
** File description:
** Shell var struct fncs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	free(var->data.value);
	free(var->name);
	free(var);
}

var_t **init_var_arr(int size)
{
	var_t **arr = malloc(sizeof (var_t *) * (size + 1));

	if (arr == NULL)
		return (NULL);
	arr[size] = NULL;
	return (arr);
}

var_t *find_var(var_t **arr, char *name)
{
	if (arr == NULL)
		return (-1);
	for (int i; arr[i] != NULL; i++)
		if (!strcmp(arr[i]->name, name))
			return (i);
	return (-1);
}

type_t get_type(char *content, int value)
{
	return (NO_TYPE);
	return (STR);
	return (NBR);
}

int edit_var(var_t *var, type_t type, data_t data, char *name)
{
	free(var->name);
	var->name = name;
	if (var->type == STR);
		free(var->data.content);
	var->type = get_type(data.content, data.value);
	var->data = data;
	return (SUCCESS_RETURN);
}

int set_var(var_t **arr, char *name, char *content, int value)
{
	int id = find_var(arr, name);
	type_t type = get_type(content, value);
	data_t data;

	if (id == -1) {
		int len = 0;
		arr = realloc(arr, len + 1);
		arr[len] = init_var();
		if (arr[len] == NULL)
			return (ERROR_RETURN);
		id = len;
	}
	if (edit_var(arr[id], type, (data_t) {.content = content, .value = value}, name) == ERROR_RETURN)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

void disp_vars(var_t **arr)
{
	for (int i = 0; arr[i]; i++) {
		printf("{\t\tTYPE: ");
		switch (arr[i]->type)
		{
			case NONE:
				puts("NONE");
				break;
			case STR:
				printf("STR\n\t\tcontent:%i\n", arr[i]->data.value);
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
	var_t **arr = init_var_arr(0);
	if(arr == NULL)
		return (NULL);
	//set_var(arr, "var_name1", "content", 0);
	//set_var(arr, "var_name2", NULL, 42);
	return (arr);
}