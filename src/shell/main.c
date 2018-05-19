/*
** EPITECH PROJECT, 2017
** main.c
** File description:
** main file for minishell2
*/

#include <my.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

int main(int ac, char **av, char **env)
{
	shell_t *shell = init_shell(env);
	int exec = SUCCESS_CODE;

	UNUSED(av);
	UNUSED(ac);
	if (shell == NULL || init_signal() == ERROR_RETURN)
		return (ERROR_CODE);
	disp_prompt();
	while ((shell->input = gnl(STDIN_FILENO)) != NULL) {
		save_history(shell, shell->input);
		if ((shell->comm = parsing(shell->input)) == NULL)
			return (ERROR_CODE);
		for (int i = 0; shell->comm[i] != NULL; i++)
			if (replace_alias(shell->aliases, shell->comm[i]) == -1)
				return (ERROR_CODE);
		exec = exec_loop(shell);
		free_comms(shell->comm);
		if (exec == ERROR_RETURN)
			break;
		free(shell->input);
		disp_prompt();
	}
	if (shell->input == NULL && isatty(0))
		puts("exit");
	exec = shell->return_value;
	delete_shell(shell);
	return (exec);
}
