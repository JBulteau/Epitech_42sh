/*
** EPITECH PROJECT, 2017
** handler_basic.c
** File description:
** Basics andles for prompt display
*/

#include <stdio.h>
#include "minishell.h"
#include "my.h"

int ptr_modulo(shell_t *shell, char *input)
{
	UNUSED(input);
	UNUSED(shell);
	putchar('%');
	return (0);
}