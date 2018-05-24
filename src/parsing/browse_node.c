/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** browse node for 42sh
*/

#include "my.h"
#include "parsing.h"

node_t *fill_buffer(node_t *node, char *buffer, int *i)
{
	if (buffer[*i] == '\\') {
		(*i)++;
		node->backslash = true;
	}
	delete_quote(node, buffer, *i);
	return (node);
}

node_t *search_cmd_separators(node_t *node)
{
	node->next = realloc_node(node->next, 1, node->quote);
	if (node->next == NULL)
		return (NULL);
	if (node->quote == NONE)
		node->buffer = clear_str(node->buffer);
	for (int i = 0; node->buffer && node->buffer[i] != '\0'; i++) {
		node = fill_cmd_separators(node, node->buffer, &i);
		if (node == NULL)
			return (NULL);
	}
	for (int i = 0; node->next[i] != NULL; i++)
		if (node->next[i + 1] == NULL)
			node->next[i]->separator = node->separator;
	return (node);
}

node_t *browse_sep_node(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		if (node->next[i]->quote == NONE) {
			node->next[i] = \
			search_cmd_separators(node->next[i]);
		} else {
			node->next[i]->next = realloc_node\
			(node->next[i]->next, 1, node->next[i]->quote);
			node->next[i]->next[0] = \
			copy_node(node->next[i]->next[0], node->next[i]);
		}
	}
	return (node);
}

node_t *browse_glob_node(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		if (node->next[i]->quote == NONE)
			node->next[i] = \
			check_globbing(node->next[i]);
		if (node->next[i] == NULL)
			return (NULL);
	}
	return (node);
}