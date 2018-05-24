/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for struct
*/

#include "my.h"
#include "parsing.h"

node_t *copy_node(node_t *dest, node_t *src)
{
	if (dest == NULL) {
		dest = malloc(sizeof(node_t));
		if (dest == NULL)
			return (NULL);
	}
	dest->buffer = my_strndup(src->buffer, 0);
	if (dest->buffer == NULL) {
		free(dest);
		return (NULL);
	}
	dest->quote = src->quote;
	dest->separator = src->separator;
	dest->backslash = false;
	dest->next = NULL;
	return (dest);
}

node_t **realloc_node(node_t **node, int n, quote_type_t quote)
{
	node_t **new_node = malloc(sizeof(node_t*) * (n + 1));

	if (new_node == NULL)
		return (NULL);
	for (int i = 0; i < n; i++) {
		if (node != NULL && node[i] != NULL) {
			new_node[i] = \
			init_node(node[i]->buffer, node[i]->quote);
			new_node[i]->separator = node[i]->separator;
			free(node[i]->buffer);
			free(node[i]);
		} else {
			new_node[i] = init_node(NULL, quote);
		}
		if (new_node[i] == NULL)
			return (NULL);
	}
	new_node[n] = NULL;
	if (node != NULL)
		free(node);
	return (new_node);
}

node_t *init_node(char *buffer, quote_type_t quote)
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
	node->separator = 0;
	node->fg = false;
	node->backslash = false;
	node->next = NULL;
	return (node);
}
