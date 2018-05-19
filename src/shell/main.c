/*
** EPITECH PROJECT, 2017
** main.c
** File description:
** main file for minishell2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"

int run_that(shell_t *shell)
{
	int return_code = 0;

	if ((shell->comm = full_parse(shell->input)) == NULL)
		return (ERROR_CODE);
	if (update_aliases(shell, shell->comm[0], 0, 0) == ERROR_RETURN)
		return (ERROR_CODE);
	return_code = exec_loop(shell);
	if (shell->comm != NULL)
		free_comms(shell->comm);
	return (return_code);
}

int main(int ac, char **av, char **env)
{
	shell_t *shell = init_shell(env);
	int return_code = SUCCESS_CODE;

	if (shell == NULL)
		return (ERROR_CODE);
	disp_prompt();
	while ((shell->input = gnl(STDIN_FILENO)) != NULL) {
		save_history(shell, shell->input);
		return_code = run_that(shell);
		free(shell->input);
		if (return_code == -1 || return_code == -ERROR_CODE)
			break;
		disp_prompt();
	}
	if ((shell->input == NULL) && isatty(0))
		my_putstr("exit\n");
	delete_shell(shell);
	return (return_code);
}
