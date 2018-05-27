/*
** EPITECH PROJECT, 2017
** fouchauve.c
** File description:
** Ptr fouchauve
*/

#include <stdio.h>
#include "fouchauve.h"
#include "minishell.h"
#include "my.h"

int ptr_fouchauve(comm_t *comm, shell_t *shell)
{
	UNUSED(comm);
	UNUSED(shell);
	for (int i = 0; fouchauve[i]; i++)
		puts(fouchauve[i]);
	return (SUCCESS_RETURN);
}