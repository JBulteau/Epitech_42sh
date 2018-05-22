/*
** EPITECH PROJECT, 2017
** display.c
** File description:
** Display functions
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

void disp_wrong_arch(char *str, int num)
{
	printf("%s: %s. Wrong Architecture\n", str, strerror(num));
}

void display_signal(int status)
{
	if (WIFSIGNALED(status)) {
		if (WTERMSIG(status) == 8)
			printf("Floating exception");
		else
			printf(strsignal(WTERMSIG(status)));
		if (WCOREDUMP(status))
			printf(" (core dumped)");
		putchar('\n');
	}
}

int disp_prompt(shell_t *shell)
{
	if (isatty(STDIN_FILENO))
		if (printf_prompt(shell) == ERROR_RETURN)
			return (ERROR_RETURN);
	fflush(stdout);
	return (SUCCESS_RETURN);
}