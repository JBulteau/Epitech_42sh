/*
** EPITECH PROJECT, 2017
** var_ptr_base.c
** File description:
** Var ptr
*/

#include <stdio.h>
#include "minishell.h"
#include "my.h"

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