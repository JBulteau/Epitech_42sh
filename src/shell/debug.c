/*
** EPITECH PROJECT, 2017
** debug.c
** File description:
** Debug functions
*/

#include <stdio.h>
#include "minishell.h"
#include "tokens.h"

void debug_comm(comm_t *comm)
{
	for (int i = 0; i < 4; i++)
		if (comm->red[i]) {
			printf("[%s] [%s]\n", tokens[i].tk, comm->red[i]->\
target);
		}
	for (int j = 0; comm->argv[j]; j++) {
		printf("%s ", comm->argv[j]);
	}
	putchar('\n');
	if (comm->pipe[OUT]) {
		puts("PIPED INTO");
		debug_comm(comm->pipe[OUT]->output);
	}
	
	switch (comm->separator)
	{
		case THEN:
			puts("&&");
			break;
		case OR:
			puts("||");
			break;
		case NONE:
			puts(";");
			break;
		default:
			break;
	}
}