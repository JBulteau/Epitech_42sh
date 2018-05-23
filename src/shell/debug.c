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

void debug_node(node_t *node)
{
	if (node && node->buffer)
		puts(node->buffer);
	for (int i = 0; node && node->next && node->next[i]; i++) {
		printf("->%s (quote = %i)\n", node->next[i]->buffer, node->next[i]->quote);
		for (int j = 0; node->next[i]->next && node->next[i]->next[j]; j++) {
			printf("-->%s (separator = %i)\n", node->next[i]->next[j]->buffer, node->next[i]->next[j]->separator);
			for (int k = 0; node->next[i]->next[j]->next && node->next[i]->next[j]->next[k]; k++) {
				printf("===>%s (separator = %i)\n", node->next[i]->next[j]->next[k]->buffer, node->next[i]->next[j]->next[k]->separator);
			}
		}
	}
}

void debug_comm(comm_t *comm)
{
	if (comm == NULL)
		return;
	for (int i = 0; i < 4; i++) {
//		printf("HERE --> %i\n", i);
		if (comm->red != NULL && comm->red[i] != NULL) {
			printf("[%s] [%s]\n", tokens[i].tk, comm->red[i]->\
target);
		}
	}
	for (int j = 0; comm->argv[j]; j++) {
		printf("%s\n", comm->argv[j]);
	}
	if (comm->argv == NULL)
		puts("No Argv");
	else if (comm->argv[0] == NULL)
		puts("First Argv NULL");
	if (comm->fg == true)
		puts("BACKGROUND");
	if (comm->pipe[OUT]) {
	 	putchar('\n');
	 	puts("PIPED INTO");
	 	debug_comm(comm->pipe[OUT]->output);
	}
	putchar('\n');
	switch (comm->separator) {
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
	putchar('\n');
	if (comm->next)
		debug_comm(comm->next);
}