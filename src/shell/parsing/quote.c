/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** quote parsing for 42sh
*/

#include "my.h"
#include "parsing.h"

node_t *fill_buffer(node_t *node, char *buffer, int i)
{
	static int j = 0;
	static int n = 2;

	if (is_a_quote(buffer[i]) && (node->next[n - 2]->quote) == NONE) {
		if ((node->next = realloc_node(node->next, n++)) == NULL)
			return (NULL);
		j = 0;
		node->next[n - 2]->quote = index_of("'\"`", buffer[i]);
	} else if (node->next[n - 2]->quote == index_of("'\"`", buffer[i]) \
	&& node->next[n - 2]->quote != NONE) {
		if ((node->next = realloc_node(node->next, n++)) == NULL)
			return (NULL);
		j = 0;
	} else {
		if ((node->next[n - 2]->buffer = \
		realloc(node->next[n - 2]->buffer, j + 2)) == NULL)
			return (NULL);
		node->next[n - 2]->buffer[j + 1] = '\0';
		node->next[n - 2]->buffer[j++] = buffer[i];
	}
	return (node);
}

node_t *parse_quote(node_t *node, char *buffer)
{
	node->next = realloc_node(node->next, 1);
	for (int i = 0; buffer[i] != '\0'; i++) {
		if ((node = fill_buffer(node, buffer, i)) == NULL)
			return (NULL);
	}
	return (node);
}