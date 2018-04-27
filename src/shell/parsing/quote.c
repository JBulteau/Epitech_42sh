/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** quote parsing for 42sh
*/

#include "my.h"
#include "parsing.h"

int is_magic(char c)
{
	return (c == '`');
}

int is_double(char c)
{
	return (c == '"');
}

int is_simple(char c)
{
	return (c == '\'');
}

int is_a_quote(char c)
{
	return (is_simple(c) ||  is_double(c) || is_magic(c));
}

node_t *fill_buffer(node_t *node, char *buffer, int i)
{
	static int j = 0;
	static int n = 2;
	
	if (is_a_quote(buffer[i]) && !(node->next[n - 2]->quote)) {
		node->next = realloc_node(node->next, n);
		n++;
		j = 0;
		node->next[n - 2]->quote = index_of("'\"`", buffer[i]);
	} if (node->next[n - 2]->quote == index_of("'\"`", buffer[i])) {
		node->next = realloc_node(node->next, n);
		n++;
		j = 0;
		node->next[n - 2]->quote = NONE;
	} else {
		node->next[n - 2]->buffer = \
		realloc(node->next[n - 2]->buffer, j + 2);
		node->next[n - 2]->buffer[j] = buffer[i];
	}
	return (node);
}

node_t *parse_quote(node_t *node, char *buffer)
{
	node->next = realloc_node(node->next, 1);
	for (int i = 0; buffer[i] != '\0'; i++) {
		node = fill_buffer(node, buffer, i);
	}
	return (node);
}