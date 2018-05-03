/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** parentheses parsing for 42sh
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

node_t *check_parentheses(node_t *node, char *buffer)
{
	int i;
	int j;

	for (i = 0; buffer[i] == ' ' || buffer[i] == '\t'; i++);
	for (j = (strlen(node->buffer) - 1); buffer[j] == ' ' \
	|| buffer[j] == '\t'; j--);
	if (node->buffer[i] == '(' && node->buffer[j] == ')') {
		node->buffer[i] = ' ';
		node->buffer[j] = ' ';
		node->quote = PARENTHESES;
	}
	return (node);
}

static node_t *roll_node(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		if (node->next[i]->quote == NONE)
			node->next[i] = \
			check_parentheses(node->next[i], node->next[i]->buffer);
		if (node->next[i] == NULL)
			return (NULL);
	}
	return (node);
}

node_t *parse_parentheses(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		node->next[i] = roll_node(node->next[i]);
		if (node == NULL)
			return (NULL);
	}
	return (node);
}