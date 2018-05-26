/*
** EPITECH PROJECT, 2017
** handler_get_from_shell.c
** File description:
** Functions handle that juste get infos from shell
*/

#include <stdio.h>
#include "prompt.h"
#include "minishell.h"
#include "my.h"

int ptr_handle_return(shell_t *shell, char *input)
{
	UNUSED(input);
	printf("%i", shell->return_value);
	return (SUCCESS_RETURN);
}

int ptr_handle_pwd(shell_t *shell, char *input)
{
	UNUSED(input);
	printf("%s", shell->pwd[0]);
	return (SUCCESS_RETURN);
}

int ptr_handle_history(shell_t *shell, char *input)
{
	int i = 0;

	UNUSED(input);
	for (history_t *curr = shell->history; curr; curr = curr->next)
		i++;
	printf("%i", i);
	return (SUCCESS_RETURN);
}

int ptr_handle_jobs(shell_t *shell, char *input)
{
	UNUSED(shell);
	UNUSED(input);
	printf("%d", get_nb_job());
	return (SUCCESS_RETURN);
}