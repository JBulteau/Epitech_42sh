/*
** EPITECH PROJECT, 2017
** display.c
** File description:
** Display functions
*/

#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"


void disp_wrong_arch(char *str, int errno)
{
	my_putstr(str);
	my_putstr(": ");
	my_putstr(strerror(errno));
	my_putstr(". Wrong Architecture\n");
}

void display_signal(int status)
{
	if (WIFSIGNALED(status)) {
		if (WTERMSIG(status) == 8)
			my_putstr("Floating exception");
		else
			my_putstr(strsignal(WTERMSIG(status)));
		if (WCOREDUMP(status))
			my_putstr(" (core dumped)");
		my_putchar('\n');
	}
}

void disp_prompt(void)
{
	if (isatty(STDIN_FILENO))
		my_putstr(prompt);
}