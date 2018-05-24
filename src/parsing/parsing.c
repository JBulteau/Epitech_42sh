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
	if (comm == NULL)
		return (NULL);
	comm = convert_node(comm, node);
	free_node(node);
	return (comm);
}