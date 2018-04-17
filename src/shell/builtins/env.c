/*
** EPITECH PROJECT, 2017
** env.c
** File description:
** Env fnc
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

int add_env_value(char ***env, char *var, char *value, char *var_pre)
{
	char **new_env = NULL;
	int len = array_len((void **) (*env));

	if ((new_env = malloc(sizeof(char **) * (len + 1))) == NULL)
		return (-1);
	for (int i = 0; (*env)[i] != NULL; i++)
		new_env[i] = (*env)[i];
	if ((new_env[len - 1] = concat(var_pre, value, 1, 0)) == NULL)
		return (-1);
	new_env[len] = NULL;
	free((*env));
	(*env) = new_env;
	return (0);
}

int set_env_value(char ***env, char *var, char *value)
{
	char *var_pre = concat(var, "=", 0, 0);
	int env_idx = search_strtab((*env), var_pre);

	value = (value == NULL) ? my_strndup("", 0) : value;
	if (index_of(ALPHA_LOW, var[0]) == -1 && index_of(ALPHA_UP, var[0]) == -1) {
		my_putstr("setenv: Variable name must begin with a letter.\n");
		return (1);
	} else if (is_alphanum(var) == -1) {
		my_putstr("setenv: Variable name must contain alphanumeric characters.\n");
		return (1);
	}
	if (env_idx != -1) {
		free((*env)[env_idx]);
		if (((*env)[env_idx] = concat(var_pre, value, 1, 0)) == NULL)
			return (-1);
	} else if (add_env_value(env, var, value, var_pre) == -1) {
		return (-1);
	}
	return (0);
}

int ptr_env(comm_t *comm, char ***env, char pwd[2][PATH_MAX])
{
	for (int i = 0; (*env)[i] != NULL; i++) {
		my_putstr((*env)[i]);
		my_putchar('\n');
	}
	return (0);
}

int ptr_setenv(comm_t *comm, char ***env, char pwd[2][PATH_MAX])
{
	if (comm->argv[1] == NULL) {
		for (int i = 0; (*env)[i] != NULL; i++) {
			my_putstr((*env)[i]);
			my_putchar('\n');
		}
		return (0);
	}
	return (set_env_value(env, comm->argv[1], comm->argv[2]));
}

int ptr_unsetenv(comm_t *comm, char ***env, char pwd[2][PATH_MAX])
{
	int index;
	char *value;

	if (comm->argv[1] == NULL) {
		my_putstr("unsetenv: Too few arguments.\n");
		return (1);
	}
	for (int arg = 1; comm->argv[arg]; arg++) {
		index = search_strtab(*env, comm->argv[arg]);
		if (index == -1)
			continue;
		value = (*env)[index];
		for (int i = index; (*env)[i]; i++)
			(*env)[i] = (*env)[i + 1];
		free(value);
	}
	return (0);
}