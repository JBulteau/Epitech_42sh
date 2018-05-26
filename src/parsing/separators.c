/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

comm_t *simple_separators(comm_t *comm, node_t *node[2], int new_index[2], \
shell_t *shell)
{
	comm->separator = new_index[0] - 1;
	if (new_index[0] > SEMICOLON) {
		comm->next = init_comm();
		if (comm->next == NULL)
			return (NULL);
		comm->next = \
		fill_comm(comm->next, node[1], &new_index[1], shell);
		if (comm->next == NULL)
			return (NULL);
	}
	return (comm);
}

comm_t *simple_pipe(comm_t *comm, node_t *node[2], int new_index[2], \
shell_t *shell)
{
	comm->pipe[OUT] = init_pipe(comm, init_comm());
	if (comm->pipe[OUT] == NULL)
		return (NULL);
	comm->pipe[OUT]->output = fill_comm\
	(comm->pipe[OUT]->output, node[1], &new_index[1], shell);
	if (comm->pipe[OUT]->output == NULL)
		return (NULL);
	return (comm);
}

comm_t *redir(comm_t *comm, node_t *node[2], int new_index[2])
{
	comm->red[new_index[0] - 6] = init_redir();
	if (comm->red[new_index[0] - 6] == NULL)
		return (NULL);
	comm->red[new_index[0] - 6]->target = \
	strdup(node[0]->buffer);
	if (comm->red[new_index[0] - 6]->target == NULL)
		return (NULL);
	return (comm);
}

comm_t *ampersand(comm_t *comm, node_t *node[2], int new_index[2])
{
	comm->bg = true;
	if (REDIR(new_index[0]) && comm->red[new_index[0] - 6] \
	&& comm->red[new_index[0] - 6]->target == NULL)
		return (NULL);
	return (comm);
}