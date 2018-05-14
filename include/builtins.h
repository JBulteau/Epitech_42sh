/*
** EPITECH PROJECT, 2017
** builtins.h
** File description:
** builtins for minishell
*/

#ifndef __BUILTINS__
#define __BUILTINS__

#include "minishell.h"

int ptr_cd(comm_t *comm, shell_t *shell);
int ptr_env(comm_t *comm, shell_t *shell);
int ptr_setenv(comm_t *comm, shell_t *shell);
int ptr_unsetenv(comm_t *comm, shell_t *shell);
int ptr_exit(comm_t *comm, shell_t *shell);
int ptr_history(comm_t *comm, shell_t *shell);
int ptr_fg(comm_t *comm, shell_t *shell);

static const struct {
	char *name;
	int (*fnc)(comm_t *comm, shell_t *shell);
} builtins[] = {
	{"cd", &ptr_cd},
	{"env", &ptr_env},
	{"setenv", &ptr_setenv},
	{"unsetenv", &ptr_unsetenv},
	{"exit", &ptr_exit},
	{"history", &ptr_history},
	{"fg", &ptr_fg},
	{NULL, NULL}
};

#endif
