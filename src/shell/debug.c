/*
** EPITECH PROJECT, 2017
** debug.c
** File description:
** Debug functions
*/

#include "my.h"
#include "minishell.h"
#include "tokens.h"

void debug_comm(comm_t *comm)
{
	for (int i = 0; i < 4; i++)
		if (comm->red[i]) {
			my_putchar('[');
			my_putstr(tokens[i].tk);
			my_putstr("] [");
			my_putstr(comm->red[i]->target);
			my_putstr("]\n");
		}
	for (int j = 0; comm->argv[j]; j++) {
		my_putstr(comm->argv[j]);
		my_putchar(' ');
	}
	my_putchar('\n');
	if (comm->pipe) {
		my_putstr("PIPED INTO\n");
		debug_comm(comm->pipe);
	}
}