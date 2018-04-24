/*
** EPITECH PROJECT, 2017
** basic_bi.c
** File description:
** Basic built-ins fnc
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "builtins.h"
#include "minishell.h"

int ptr_exit(comm_t *comm, shell_t *shell)
{
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
	if ((comm == NULL) || (shell->env == NULL) || (shell->pwd == NULL))
		return (-1);
	return (builtins[is_builtin(comm->argv[0])].fnc(comm, shell));
}
