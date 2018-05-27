/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** quote parsing for 42sh
*/

#include "my.h"
#include "parsing.h"
#include <stdio.h>

int missing_quote(node_t *node, char *buffer)
{
	int i;
	int j;

	for (i = 0; node->next[i + 1] != NULL; i++);
	for (j = 0; buffer[j + 1] != '\0'; j++);
	if (node->next[i]->quote != NONE && !is_a_quote(buffer[j])) {
		if (node->next[i]->quote == SIMPLE)
			fprintf(stderr, "Unmatched '''.\n");
		else if (node->next[i]->quote == DOUBLE)
			fprintf(stderr, "Unmatched '\"'.\n");
		else
			fprintf(stderr, "Unmatched '`'.\n");
		return (1);
	}
	if (node->next[i]->quote == NONE && is_a_quote(buffer[j])) {
		fprintf(stderr, "Unmatched '%c'.\n", buffer[j]);
		return (1);
	}
	return (0);
}

node_t *no_quote(node_t *node, char *buffer, int i, int *j)
{
	if ((node->buffer = \
	realloc(node->buffer, (*j) + 2)) == NULL)
		return (NULL);
	node->buffer[(*j)] = buffer[i];
	node->buffer[(*j) + 1] = '\0';
	(*j)++;
	return (node);
}

node_t *new_quoted_node(node_t *node, int index[], char *buffer, int i)
{
	if (node->next[index[1] - 2]->buffer != NULL)
		node->next = \
		realloc_node(node->next, (index[1])++, node->quote);
	index[0] = 0;
	if (node->next != NULL)
		node->next[index[1] - 2]->quote = index_of("'\"`", buffer[i]);
	return (node);
}

node_t *delete_quote(node_t *node, char *buffer, int i)
{
	static int index[2] = {0, 2};

	index[0] = (i == 0) ? 0 : index[0];
	index[1] = (i == 0) ? 2 : index[1];
	if (is_a_quote(buffer[i]) && (node->next[index[1] - 2]->quote) == NONE \
	&& !node->backslash && buffer[i + 1] != '\0') {
		node = new_quoted_node(node, index, buffer, i);
	} else if (node->next[index[1] - 2]->quote == \
	index_of("'\"`", buffer[i]) && node->next[index[1] - 2]->quote != NONE \
	&& !node->backslash) {
		if ((index[0] = 0) == 0 || buffer[i + 1] == '\0')
			return (node);
		else if ((node->next = \
		realloc_node(node->next, index[1]++, node->quote)) == NULL)
			return (NULL);
	} else {
		node->next[index[1] - 2] = no_quote(node->next[index[1] - 2], \
		buffer, i, &index[0]);
		node->backslash = false;
	}
	return ((node->next == NULL) ? NULL : node);
}

node_t *parse_quote(node_t *node, shell_t *shell)
{
	node->next = realloc_node(node->next, 1, node->quote);
	if (node->next == NULL)
		return (NULL);
	for (int i = 0; shell->input[i] != '\0'; i++) {
		node = fill_buffer(node, shell->input, &i);
		if (node == NULL)
			return (NULL);
	}
	if (missing_quote(node, shell->input)) {
		free_node(node);
		return (NULL);
	}
	if (!check_double_separator(node)) {
		free_node(node);
		return (NULL);
	}
	node = handle_aliases(node, shell);
	node = handle_variables(node, shell);
	return ((node == NULL) ? NULL : parse_split(node));
}
