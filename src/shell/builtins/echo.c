/*
** EPITECH PROJECT, 2017
** echo.c
** File description:
** Builtin echo
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

int ptr_echo(comm_t *comm, shell_t *shell)
{
	int nl = 0;

	UNUSED(shell);
	if (comm == NULL || comm->argv[1] == NULL)
		return (putchar('\n') == 42);
	nl = strcmp(comm->argv[1], "-n");
	for (int i = 1 + !nl; comm->argv[i]; i++) {
		printf(comm->argv[i]);
		if (comm->argv[i + 1])
			putchar(' ');
	}
	if (nl)
		putchar('\n');
	return (SUCCESS_RETURN);
}