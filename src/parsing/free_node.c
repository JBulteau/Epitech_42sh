/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** destroy parse nodes
*/

#include "my.h"
#include "parsing.h"

void free_node(node_t *node)
{
	if (node == NULL)
		return;
	if (node->next != NULL) {
		for (int i = 0; node->next[i] != NULL; i++)
			free_node(node->next[i]);
		free(node->next);
	}
	if (node->buffer != NULL)
		free(node->buffer);
	free(node);
}