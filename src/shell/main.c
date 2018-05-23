/*
** EPITECH PROJECT, 2017
** main.c
** File description:
** main file for minishell2
*/

#include <my.h>
#include "my.h"
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
		shell->return_value = run_that(shell);
		free(shell->input);
		disp_prompt();
	}
	if (shell->input == NULL && isatty(0))
		puts("exit");
	exec = shell->return_value;
	delete_shell(shell);
	return (exec);
}