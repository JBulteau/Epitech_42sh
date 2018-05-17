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
	node_t *node = init_node(buffer, NONE, 0);

	if (node == NULL)
		return (NULL);
	node = parse_quote(node, buffer);
}