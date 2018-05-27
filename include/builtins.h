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
int ptr_exec_his(comm_t *comm, shell_t *shell);
int ptr_fg(comm_t *comm, shell_t *shell);
int ptr_jobs(comm_t *comm, shell_t *shell);
int ptr_alias(comm_t *comm, shell_t *shell);
int ptr_unalias(comm_t *comm, shell_t *shell);
int ptr_echo(comm_t *comm, shell_t *shell);
int ptr_repeat(comm_t *comm, shell_t *shell);
int ptr_at(comm_t *comm, shell_t *shell);
int ptr_set(comm_t *comm, shell_t *shell);
int ptr_unset(comm_t *comm, shell_t *shell);
int ptr_builtins(comm_t *comm, shell_t *shell);
int ptr_dirs(comm_t *comm, shell_t *shell);
int ptr_at(comm_t *comm, shell_t *shell);
int ptr_printenv(comm_t *comm, shell_t *shell);
int ptr_where(comm_t *comm, shell_t *shell);
int ptr_which(comm_t *comm, shell_t *shell);
int ptr_source(comm_t *comm, shell_t *shell);
int ptr_fouchauve(comm_t *comm, shell_t *shell);

static const struct {
	char *name;
	int (*fnc)(comm_t *comm, shell_t *shell);
} builtins[] = {
	{"builtins", &ptr_builtins},
	{"cd", &ptr_cd},
	{"env", &ptr_env},
	{"setenv", &ptr_setenv},
	{"unsetenv", &ptr_unsetenv},
	{"exit", &ptr_exit},
	{"history", &ptr_history},
	{"!", &ptr_exec_his},
	{"fg", &ptr_fg},
	{"jobs", &ptr_jobs},
	{"alias", &ptr_alias},
	{"unalias", &ptr_unalias},
	{"echo", &ptr_echo},
	{"fouchauve", &ptr_fouchauve},
	{"repeat", &ptr_repeat},
	{"@", &ptr_at},
	{"set", &ptr_set},
	{"unset", &ptr_unset},
	{"chdir", &ptr_cd},
	{"dirs", &ptr_dirs},
	{"@", &ptr_at},
	{"printenv", &ptr_printenv},
	{"which", &ptr_which},
	{"where", &ptr_where},
	{"source", &ptr_source},
	{NULL, NULL}
};

#endif
