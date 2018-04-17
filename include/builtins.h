/*
** EPITECH PROJECT, 2017
** builtins.h
** File description:
** builtins for minishell
*/

#ifndef __BUILTINS__
#define __BUILTINS__

#include "minishell.h"

int ptr_cd(comm_t *comm, char ***env, char [2][PATH_MAX]);
int ptr_env(comm_t *comm, char ***env, char [2][PATH_MAX]);
int ptr_setenv(comm_t *comm, char ***env, char [2][PATH_MAX]);
int ptr_unsetenv(comm_t *comm, char ***env, char [2][PATH_MAX]);
int ptr_exit(comm_t *comm, char ***env, char [2][PATH_MAX]);

static const struct {
	char *name;
	int (*fnc)(comm_t *comm, char ***env, char [2][PATH_MAX]);
} builtins[] = {
	{"cd", &ptr_cd},
	{"env", &ptr_env},
	{"setenv", &ptr_setenv},
	{"unsetenv", &ptr_unsetenv},
	{"exit", &ptr_exit},
	{NULL, NULL}
};

#endif