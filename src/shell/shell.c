/*
** EPITECH PROJECT, 2017
** shell.c
** File description:
** Main shell functions
*/

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"

char **clone_arr(char **arr)
{
	int len = array_len((void *) arr);
	char **new_arr = NULL;

	if (len == -1) {
		new_arr = malloc(sizeof(char *) * 1);
		if (new_arr == NULL)
			return (NULL);
		new_arr[0] = NULL;
	} else {
		new_arr = malloc(sizeof(char *) * len);
		if (new_arr == NULL)
			return (NULL);
		for (int i = 0; arr[i]; i++)
			new_arr[i] = my_strndup(arr[i], 0);
		new_arr[len - 1] = NULL;
	}
	return (new_arr);
}

shell_t *init_shell(char **env)
{
	shell_t *shell = malloc(sizeof(shell_t));

	if (shell == NULL || (shell->env = clone_arr(env)) == NULL)
		return (NULL);
	shell->return_value = 0;
	shell->history = NULL;
	//if (load42(shell) == ERROR_RETURN)
	//	return (NULL);
	getcwd(shell->pwd[0], PATH_MAX);
	for (int i = 0; i < PATH_MAX; i++)
		shell->pwd[1][i] = '\0';
	return (shell);
}

void delete_shell(shell_t *shell)
{
	if (shell == NULL)
		return;
	free_array((void **) shell->env);
	free_history(shell->history);
	free(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
