/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for struct
*/

#include "my.h"
#include "parsing.h"

node_t **realloc_node(node_t **node, int n)
{
	node_t **new_node = malloc(sizeof(node_t*) * (n + 1));

	if (new_node == NULL)
		return (NULL);
	for (int i = 0; i < n; i++) {
		if (node != NULL && node[i] != NULL) {
			new_node[i] = \
			init_node(node[i]->buffer, node[i]->quote);
			free(node[i]->buffer);
			free(node[i]);
		} else {
			new_node[i] = init_node(NULL, NONE);
		}
		if (new_node[i] == NULL)
			return (NULL);
	}
	new_node[n] = NULL;
	if (node != NULL)
		free(node);
	return (new_node);
}

node_t *init_node(char *buffer, int quote)
{
	node_t *node = malloc(sizeof(node_t));

	if (node == NULL)
		return (NULL);
	if (buffer != NULL) {
		node->buffer = my_strndup(buffer, 0);
		if (node->buffer == NULL) {
			free(node);
			return (NULL);
		}
	} else {
		node->buffer = NULL;
	}
	node->quote = quote;
	node->backslash = false;
	node->next = NULL;
	return (node);
}