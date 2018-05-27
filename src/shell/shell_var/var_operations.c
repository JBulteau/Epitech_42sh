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

int ptr_plusplus(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	UNUSED(n);
	if (id == ERROR_RETURN)
		shell->vars = set_var(shell->vars, name, "1");
	else
		shell->vars[id]->data.value++;
	return (0);
}

int ptr_plus(char *name, int n, shell_t *shell)
{
	char buff[512];
	int id = find_var(shell->vars, name);

	if (id == ERROR_RETURN) {
		sprintf(buff, "%i", n);
		shell->vars = set_var(shell->vars, name, buff);
	} else
		shell->vars[id]->data.value += n;
	return (0);
}

int ptr_minmin(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	UNUSED(n);
	if (id == ERROR_RETURN)
		shell->vars = set_var(shell->vars, name, "-1");
	else
		shell->vars[id]->data.value--;
	return (0);
}

int ptr_min(char *name, int n, shell_t *shell)
{
	char buff[512];
	int id = find_var(shell->vars, name);

	if (id == ERROR_RETURN) {
		sprintf(buff, "%i", n);
		shell->vars = set_var(shell->vars, name, buff);
	} else
		shell->vars[id]->data.value -= n;
	return (0);
}

int ptr_mul(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	if (id == ERROR_RETURN) {
		shell->vars = set_var(shell->vars, name, "0");
	} else
		shell->vars[id]->data.value *= n;
	return (0);
}

int ptr_div(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	if (id == ERROR_RETURN) {
		shell->vars = set_var(shell->vars, name, "0");
	} else
		shell->vars[id]->data.value /= n;
	return (0);
}

int ptr_mod(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	if (id == ERROR_RETURN) {
		shell->vars = set_var(shell->vars, name, "0");
	} else
		shell->vars[id]->data.value %= n;
	return (0);
}

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
	int id = find_ope(arg);

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