/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions to check valid buffer
*/

#include "my.h"
#include "parsing.h"
#include <stdio.h>
#include <string.h>

comm_t *check_redir(comm_t *comm)
{
	for (int i = 0; i < 4; i++) {
		if (comm->red[i] && comm->red[i]->target == NULL) {
			free_comm(comm);
			return (NULL);
		}
	}
	return (comm);
}

comm_t *check_pipe(comm_t *comm)
{
	if (comm->pipe[OUT]) {
		if ((comm->pipe[OUT]->output = \
		check_comm(comm->pipe[OUT]->output)) == NULL) {
			free_comm(comm);
			return (NULL);
		}
	}
	return (comm);
}

comm_t *check_next(comm_t *comm)
{
	if (comm->next) {
		if ((comm->next = check_comm(comm->next)) == NULL) {
			free_comm(comm);
			return (NULL);
		}
	}
	return (comm);
}

int check_buffer(char **buffer)
{
	*buffer = clear_str(*buffer);
	if (strlen(*buffer) < 3)
		return (1);
	for  (int i = 0; (*buffer)[i + 2]; i++) {
		if ((is_separator_char((*buffer)[i]) \
		&& is_separator_char((*buffer)[i + 2])) \
		&& !((*buffer)[i] == ';' && (*buffer)[i + 2] == ';'))
			return (0);
	}
	return (1);
}

int check_double_separator(node_t *node)
{	
	for (int i = 0; node && node->next[i]; i++) {
		while (node->next[i] && node->next[i]->quote != NONE)
			i++;
		if (!node->next[i])
			break;
		if (!check_buffer(&node->next[i]->buffer)) {
			fprintf(stderr, "Invalid null command.\n");
			return (0);
		}
	}
	return (1);
}