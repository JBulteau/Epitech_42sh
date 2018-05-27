/*
** EPITECH PROJECT, 2017
** env.c
** File description:
** Env fnc
*/

#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

int add_env_value(char ***env, char *value, char *var_pre)
{
	char **new_env = NULL;
	int len = array_len((void **) (*env));

	if ((new_env = malloc(sizeof(char **) * (len + 1))) == NULL)
		return (ERROR_RETURN);
	for (int i = 0; (*env)[i] != NULL; i++)
		new_env[i] = (*env)[i];
	if ((new_env[len - 1] = concat(var_pre, value, 1, 0)) == NULL)
		return (ERROR_RETURN);
	new_env[len] = NULL;
	free((*env));
	(*env) = new_env;
	return (SUCCESS_RETURN);
}

int set_env_value(char ***env, char *var, char *value)
{
	char *var_pre = concat(var, "=", 0, 0);
	int env_idx = search_strtab((*env), var_pre);

	value = (value == NULL) ? strdup("") : value;
	if (isalpha(var[0]) == 0) {
		puts("setenv: Variable name must begin with a letter.");
		return (EXIT_FAILURE);
	} else if (is_alphanum(var) == -1) {
		puts("setenv: Variable name must contain alphanumeric characte\
rs.");
		return (EXIT_FAILURE);
	}
	if (env_idx != -1) {
		free((*env)[env_idx]);
		if (((*env)[env_idx] = concat(var_pre, value, 1, 0)) == NULL)
			return (ERROR_RETURN);
	} else if (add_env_value(env, value, var_pre) == ERROR_RETURN) {
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int ptr_env(comm_t *comm, shell_t *shell)
{
	UNUSED(comm);
	if (shell == NULL || shell->env == NULL)
		return (EXIT_FAILURE);
	for (int i = 0; shell->env[i] != NULL; i++)
		puts(shell->env[i]);
	return (SUCCESS_RETURN);
}

int ptr_setenv(comm_t *comm, shell_t *shell)
{
	if (shell == NULL || shell->env == NULL)
		return (ERROR_RETURN);
	if (comm->argv[1] == NULL) {
		for (int i = 0; shell->env[i] != NULL; i++)
			puts(shell->env[i]);
		return (SUCCESS_RETURN);
	}
	return (set_env_value(&shell->env, comm->argv[1], comm->argv[2]));
}

int ptr_unsetenv(comm_t *comm, shell_t *shell)
{
	int index;
	char *value;

	if (comm == NULL || shell == NULL || shell->env == NULL)
		return (EXIT_FAILURE);
	if (comm->argv[1] == NULL) {
		puts("unsetenv: Too few arguments.");
		return (EXIT_FAILURE);
	}
	for (int arg = 1; comm->argv[arg]; arg++) {
		index = search_strtab(shell->env, comm->argv[arg]);
		if (index == -1)
			continue;
		value = shell->env[index];
		for (int i = index; shell->env[i]; i++)
			shell->env[i] = shell->env[i + 1];
		free(value);
	}
	return (EXIT_SUCCESS);
}
