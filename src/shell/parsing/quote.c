/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** quote parsing for 42sh
*/

#include "my.h"
#include "parsing.h"
#include <stdio.h>
#include <unistd.h>

int missing_quote(node_t *node, char *buffer)
{
	int i;
	int j;

	for (i = 0; node->next[i + 1] != NULL; i++);
	for (j = 0; buffer[j + 1] != '\0'; j++);
	if (node->next[i]->quote != NONE && !is_a_quote(buffer[j])) {
		if (node->next[i]->quote == SIMPLE)
			dprintf(STDERR_FILENO, "Unmatched '''.\n");
		else if (node->next[i]->quote == DOUBLE)
			dprintf(STDERR_FILENO, "Unmatched '\"'.\n");
		else
			dprintf(STDERR_FILENO, "Unmatched '`'.\n");
		return (1);
	}
	return (0);
}

node_t *delete_quote(node_t *node, char *buffer, int i)
{
	static int j = 0;
	static int n = 2;

	if (is_a_quote(buffer[i]) && (node->next[n - 2]->quote) == NONE \
	&& !node->backslash) {
		if (node->next[n - 2]->buffer != NULL)
			node->next = realloc_node(node->next, n++);
		if (node->next == NULL)
			return (NULL);
		j = 0;
		node->next[n - 2]->quote = index_of("'\"`", buffer[i]);
	} else if (node->next[n - 2]->quote == index_of("'\"`", buffer[i]) \
	&& node->next[n - 2]->quote != NONE && !node->backslash) {
		if ((node->next = realloc_node(node->next, n++)) == NULL)
			return (NULL);
		j = 0;
	} else {
		if ((node->next[n - 2]->buffer = \
		realloc(node->next[n - 2]->buffer, j + 2)) == NULL)
			return (NULL);
		node->next[n - 2]->buffer[j + 1] = '\0';
		node->next[n - 2]->buffer[j++] = buffer[i];
		node->backslash = false;
	}
	return (node);
}

node_t *fill_buffer(node_t *node, char *buffer, int *i)
{
	if (buffer[*i] == '\\') {
		(*i)++;
		node->backslash = true;
	}
	delete_quote(node, buffer, *i);
	return (node);
}

node_t *parse_quote(node_t *node, char *buffer)
{
	node->next = realloc_node(node->next, 1);
	if (node->next == NULL)
		return (NULL);
	for (int i = 0; buffer[i] != '\0'; i++) {
		node = fill_buffer(node, buffer, &i);
		if (node == NULL)
			return (NULL);
	}
	if (missing_quote(node, buffer))
		return (NULL);
	return (parse_split(node));
}
