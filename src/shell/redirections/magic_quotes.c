/*
** EPITECH PROJECT, 2017
** magic_quotes.c
** File description:
** MAgic quotes functions
*/

#include <stddef.h>
#include "minishell.h"

char *get_magic(shell_t *shell, char *comm)
{
	char *magic = NULL;
	shell_t *dup_shell = dup_shell(shell);

	dup_shell->input = comm;
	if (run_that(dup_shell) == -ERROR_CODE)
		break;
	delete_shell(dup_shell);
	return (strdup("Ceci arrive julo"));
}