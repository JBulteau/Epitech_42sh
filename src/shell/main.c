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
	size_t size;
	shell_t *shell = init_shell(env);
	int return_code = SUCCESS_CODE;

	if (shell == NULL || init_signal() == -1)
		return (ERROR_CODE);
	disp_prompt();
	while (getline(&(shell->input), &size, stdin) != -1) {
		if (shell->input[strlen(shell->input) - 1] == '\n')
			shell->input[strlen(shell->input) - 1] = 0;
		save_history(shell, shell->input);
		if ((shell->comm = full_parse(shell->input)) == NULL)
			return (ERROR_CODE);
		for (int i = 0; shell->comm[i] != NULL; i++)
			if (replace_alias(shell->aliases, shell->comm[i]) == -1)
				return (ERROR_CODE);
		return_code = exec_loop(shell);
		free_comms(shell->comm);
		free(shell->input);
		if (return_code == -1 || return_code == -ERROR_CODE)
			break;
		disp_prompt();
	}
	if ((shell->input == NULL) && isatty(0))
		puts("exit");
	delete_shell(shell);
	return (return_code);
}
