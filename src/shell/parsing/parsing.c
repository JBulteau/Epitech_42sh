/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** functions for args parsing
*/

#include "my.h"
#include "parsing.h"

comm_t **parsing(char *buffer)
{
	node_t *node = init_node(buffer, NONE);
	comm_t **comm = NULL;

	if (node == NULL)
		return (NULL);
	node = parse_quote(node, buffer);
	if (node == NULL)
		return (NULL);
	comm = init_comm_array(comm, node);
	comm = convert_node(comm, node);
	debug_comm(comm[0]);
	debug_comm(comm[0]->pipe[OUT]->output);
	free_node(node);
	return (comm);
}