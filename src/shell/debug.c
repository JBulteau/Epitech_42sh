/*
** EPITECH PROJECT, 2017
** debug.c
** File description:
** Debug functions
*/

#include <stdio.h>
#include "minishell.h"
#include "tokens.h"
#include "parsing.h"

void display_sep(sep_t separator)
{
	switch (separator) {
	case THEN:
		puts("&&");
		break;
	case OR:
		puts("||");
		break;
	case NOTHING:
		puts(";");
		break;
	}
}

void debug_comm(comm_t *comm)
{
	if (comm == NULL)
		return;
	for (int i = 0; i < 4; i++)
		if (comm->red != NULL && comm->red[i] != NULL)
			printf("[%s] [%s]\n", tokens[i].tk, comm->red[i]->\
target);
	for (int j = 0; comm->argv[j]; j++)
		puts(comm->argv[j]);
	if (comm->bg == true)
		puts("BACKGROUND");
	if (comm->pipe[OUT]) {
		putchar('\n');
		puts("PIPED INTO");
		debug_comm(comm->pipe[OUT]->output);
	}
	putchar('\n');
	display_sep(comm->separator);
	putchar('\n');
	if (comm->next)
		debug_comm(comm->next);
}