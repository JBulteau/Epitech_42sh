/*
** EPITECH PROJECT, 2017
** dirs.c
** File description:
** dirs builtin fncs
*/

#include <stdio.h>
#include "my.h"
#include "minishell.h"

int ptr_dirs(comm_t *comm, shell_t *shell)
{
	UNUSED(comm);
	puts(shell->pwd[0]);
	return (SUCCESS_RETURN);
}