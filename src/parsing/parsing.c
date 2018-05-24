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
	if (buffer == NULL || buffer[0] == '\0') {
		free_node(node);
		return (NULL);
	}
	node = parse_quote(node, buffer);
	if (node == NULL)
		return (NULL);
	comm = init_comm_array(comm, node);
	comm = convert_node(comm, node);
	if ((comm && !comm[0]) || (comm && comm[0] && !comm[0]->argv) \
	|| (comm && comm[0] && comm[0]->argv && !comm[0]->argv[0])) {
		free_comms(comm);
		comm = NULL;
	}
	free_node(node);
	return (comm);
}