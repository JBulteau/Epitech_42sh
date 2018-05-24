/*
** EPITECH PROJECT, 2017
** vars.c
** File description:
** Builtin set
*/

#include <stdio.h>
#include "minishell.h"
#include "my.h"

static int disp_vars(var_t **vars)
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

int ptr_set(comm_t *comm, shell_t *shell)
{
	if (comm->argv[1] == NULL)
		return (disp_vars(shell->vars));
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
	return (SUCCESS_RETURN);
}