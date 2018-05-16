/*
** EPITECH PROJECT, 2017
** echo.c
** File description:
** Builtin echo
*/

#include <unistd.h>
#include "minishell.h"
#include "my.h"

int ptr_echo(comm_t *comm, shell_t *shell)
{
        if (comm->argv[1] == NULL) {
                putchar('\n');
                return (SUCCESS_RETURN);
        }
        for (int i = 1; comm->argv[i]; i++) {
                printf(comm->argv[i]);
                if (comm->argv[i + 1])
                        putchar(' ');
        }
        putchar('\n');
	return (SUCCESS_RETURN);
}