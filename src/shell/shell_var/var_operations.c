/*
** EPITECH PROJECT, 2017
** var_operations.c
** File description:
** Function for vars operations
*/

#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"
#include "vars.h"

ope_t find_ope(char *arg)
{
	for (int i = 0; vars_ope[i].op_txt; i++) {
		if (!strncmp(vars_ope[i].op_txt, arg, \
		strlen(vars_ope[i].op_txt)))
			return (i);
	}
	return (ERROR_RETURN);
}

char *get_var_name(char *arg, int *j)
{
	char *index = strpbrk(arg, "*+-/%=");

	if (index == NULL)
		return (NULL);
	(*j) += (int) (index - arg);
	index = strndup(arg, (int) (index - arg));
	return (index);
}

ope_t get_op(char *arg, int *j)
{
	puts(arg);
	int id = find_ope(arg);

	if (id == -1)
		return (ERR);
	if (vars_ope[id].op == PLUS_PLUS || vars_ope[id].op == MINUS_MINUS) {
		if (arg[2] != '\0') {
			puts("ERROR ++DELAMERDE");
			return (ERROR_RETURN);
		}
		(*j) += 2;
	}
	return (vars_ope[id].op);
}

int get_num(char *arg, int *j)
{
	arg += 2;
	(*j) = 0;
	return (atoi(arg));
}