/*
** EPITECH PROJECT, 2017
** basic_bi.c
** File description:
** Basic built-ins fnc
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my.h"
#include "builtins.h"
#include "minishell.h"

int ptr_exit(comm_t *comm, char ***env, char pwd[2][PATH_MAX], int *retrun_code)
{
	if (array_len((void **) comm->argv) > 3) {
		puts("exit: Expression Syntax.");
		*retrun_code = 1;
		return (0);
	}
	if (is_num(comm->argv[1]) == 0) {
		*retrun_code = my_getnbr(comm->argv[1]);
	} else if (is_alphanum(comm->argv[1]) == 0 && (comm->argv[1][0] >= '0'\
) && (comm->argv[1][0] <= '9')) {
		*retrun_code = 1;
		puts("exit: Badly formed number.");
		return (0);
	} else {
		*retrun_code = 1;
		puts("exit: Expression Syntax.");
		return (0);
	}
	return (-1);
}

int is_builtin(char *name)
{
	for (int i = 0; builtins[i].name != NULL; i++)
		if (!my_strcmp(builtins[i].name, name, 0))
			return (i);
	return (-1);
}

int exec_bi(comm_t *comm, shell_t *shell)
{
	int bi_no = 0;

	if ((comm == NULL) || (shell == NULL) || (shell->env == NULL) || (shell->pwd == NULL))
		return (-1);
	bi_no = is_builtin(comm->argv[0]);
	return (builtins[bi_no].fnc(comm, &(shell->env), shell->pwd, &(shell->return_value)));
}