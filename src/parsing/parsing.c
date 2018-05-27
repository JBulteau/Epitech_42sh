/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** functions for args parsing
*/

#include "my.h"
#include "parsing.h"

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
	while (comm->pipe[OUT]) {
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
	while (comm->next) {
		if ((comm->next = check_comm(comm->next)) == NULL) {
			free_comm(comm);
			return (NULL);
		}
	}
	return (comm);
}

comm_t *check_comm(comm_t *comm)
{
	comm = check_redir(comm);
	if (comm == NULL)
		return (NULL);
	comm = check_pipe(comm);
	if (comm == NULL)
		return (NULL);
	comm = check_next(comm);
	if (comm == NULL)
		return (NULL);
	if ((comm && !comm->argv) || (comm && comm->argv && !comm->argv[0])) {
		free_comm(comm);
		return (NULL);
	}
	return (comm);
}

comm_t **parsing(shell_t *shell)
{
	node_t *node = init_node(shell->input, NONE);
	comm_t **comm = NULL;

	if (node == NULL)
		return (NULL);
	if (shell->input == NULL || shell->input[0] == '\0') {
		free_node(node);
		return (NULL);
	}
	node = parse_quote(node, shell);
	if (node == NULL)
		return (NULL);
	comm = init_comm_array(comm, node);
	comm = convert_node(comm, node, shell);
	for (int i = 0; comm && comm[i]; i++)
		if ((comm[i] = check_comm(comm[i])) == NULL) {
			free_comms(comm);
			return (NULL);
		}
	free_node(node);
	return (comm);
}