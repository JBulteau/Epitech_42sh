/*
** EPITECH PROJECT, 2017
** vars.c
** File description:
** Builtin set
*/

#include <stdio.h>
#include "vars.h"
#include "minishell.h"
#include "my.h"

int disp_vars(var_t **vars)
{
	for (int i = 0; vars[i]; i++) {
		printf("%s\t", vars[i]->name);
		if (vars[i]->type == STR)
			printf("%s\n", vars[i]->data.content);
		else if (vars[i]->type == NBR)
			printf("%i\n", vars[i]->data.value);
		else
			putchar('\n');
	}
	return (SUCCESS_RETURN);
}

int ptr_unset(comm_t *comm, shell_t *shell)
{
	if (comm->argv[1] == NULL) {
		puts("unset: Too few arguments.");
		return (1);
	}
	for (int i = 1; comm->argv[i]; i++)
		unset_var(shell, comm->argv[i]);
	return (SUCCESS_RETURN);
}

int ptr_at(comm_t *comm, shell_t *shell)
{
	char *var_name;
	ope_t operation;
	int num;
	int j = 0;

	if (comm->argv[1] == NULL)
		return (ptr_set(comm, shell));
	for (int i = 1; comm->argv[i]; i++) {
		for (var_name = get_var_name(comm->argv[i], &j); !var_name;)
			break;
		operation = get_op(comm->argv[i] + j, &j);
		if (operation == ERROR_RETURN)
			break;
		else if (operation == PLUS_PLUS || operation == MINUS_MINUS) {
			vars_ope[operation].fnc(var_name, 0, shell);
		} else
			vars_ope[operation].fnc(var_name, \
(num = get_num(comm->argv[i] + j, &j)), shell);
		free(var_name);
	}
	return (SUCCESS_RETURN);
}

int ptr_set(comm_t *comm, shell_t *shell)
{
	char **token = NULL;

	if (comm->argv[1] == NULL)
		return (disp_vars(shell->vars));
	token = strwordarr(comm->argv[1], "=");
	if (token == NULL)
		return (ERROR_RETURN);
	shell->vars = set_var(shell->vars, token[0], token[1]);
	if (shell->vars == NULL)
		return (ERROR_RETURN);
	free_array((void **)token);
	return (SUCCESS_RETURN);
}