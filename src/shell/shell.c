/*
** EPITECH PROJECT, 2017
** shell.c
** File description:
** Main shell functions
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"
#include "prompt.h"
#include "my.h"

shell_t *init_shell(char **env)
{
	int create_default_env = (env == NULL || env[0] == NULL) ? 1 : 0;
	shell_t *shell = malloc(sizeof(shell_t));

	if (shell == NULL || (shell->env = clone_arr(env)) == NULL)
		return (NULL);
	shell->return_value = 0;
	shell->history_exec = 0;
	shell->history = NULL;
	shell->aliases = NULL;
	shell->input = NULL;
	for (getcwd(shell->pwd[0], PATH_MAX); !shell->pwd[0];)
		return (NULL);
	for (int i = 0; i < PATH_MAX; i++)
		shell->pwd[1][i] = '\0';
	if ((create_default_env && (setup_default_env(&(shell->env), shell) == \
ERROR_RETURN)) || (set_shlvl(&(shell->env)) == ERROR_CODE) || init_vars(shell) \
== ERROR_RETURN)
		return (NULL);
	if (isatty(STDIN_FILENO) && load42(shell) == ERROR_RETURN)
		return (NULL);
	return (shell);
}

void delete_shell(shell_t *shell)
{
	if (shell == NULL)
		return;
	free_array((void **) shell->env);
	free_history(shell->history);
	free(shell->input);
	free_aliases(shell->aliases, 1);
	for (int i = 0; shell->vars && shell->vars[i]; i++)
		free_var(shell->vars[i]);
	free(shell->vars);
	free(shell);
	if (list_jobs)
		for (; list_jobs != NULL;)
			free_jobs();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}