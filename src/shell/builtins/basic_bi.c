/*
** EPITECH PROJECT, 2017
** basic_bi.c
** File description:
** Basic built-ins fnc
*/

#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"
#include "builtins.h"

int error_msg_exit(shell_t *shell, comm_t *comm)
{
	if (array_len((void **) comm->argv) > 3) {
		puts("exit: Expression Syntax.");
		shell->return_value = 1;
		return (1);
	}
	if (list_jobs->next != NULL) {
		shell->return_value = 0;
		puts("Jobs still running (fg to continued or ctrl + D \
to quit).");
		return (1);
	}
	return (0);
}

int ptr_exit(comm_t *comm, shell_t *shell)
{
	if (error_msg_exit(shell, comm))
		return (0);
	if (comm->argv[1] == NULL) {
		shell->return_value = 0;
		return (-ERROR_CODE);
	}
	if (is_num(comm->argv[1]) == 0) {
		shell->return_value = atoi(comm->argv[1]);
		return (-ERROR_CODE);
	} else if (is_alphanum(comm->argv[1]) == 0 && (comm->argv[1][0] >= '0'\
) && (comm->argv[1][0] <= '9')) {
		shell->return_value = 1;
		puts("exit: Badly formed number.");
		return (0);
	} else {
		shell->return_value = 1;
		puts("exit: Expression Syntax.");
		return (0);
	}
	return (-ERROR_CODE);
}

int is_builtin(char *name)
{
	for (int i = 0; builtins[i].name != NULL; i++) {
		if (builtins[i].name[0] == '!' && name[0] == '!')
			return (i);
		if (!strcmp(builtins[i].name, name))
			return (i);
	}
	return (-1);
}

int exec_bi(comm_t *comm, shell_t *shell)
{
	if ((comm == NULL) || (shell == NULL) || (shell->env == NULL) || \
(shell->pwd == NULL))
		return (ERROR_RETURN);
	return (builtins[is_builtin(comm->argv[0])].fnc(comm, shell));
}
