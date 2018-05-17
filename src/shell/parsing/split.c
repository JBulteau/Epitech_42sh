/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** split parsing for 42sh
*/

#include "my.h"
#include "parsing.h"

separator_type_t is_separator(char *buffer, int *i, node_t *node)
{
	if (node->quote != NONE)
		return (0);
	switch (buffer[*i]) {
	case ';' :
		if (*i < 1 || (buffer[*i - 1] != ';' && buffer[*i - 1] != '|' \
		&& buffer[*i - 1] != '&')) {
			for (;buffer[*i + 1] == ';'; (*i)++);
			return (SEMICOLON);
		}
		break;
	case '|' :
		if ((*i < 1 || (buffer[*i - 1] != ';' && buffer[*i - 1] != '|' \
		&& buffer[*i - 1] != '&')) && buffer[(*i) + 1] == '|')
			(*i)++;
			return (D_PIPE);
		break;
	case '&' :
		if ((*i < 1 || (buffer[*i - 1] != ';' && buffer[*i - 1] != '|' \
		&& buffer[*i - 1] != '&')) && buffer[++*i] == '&')
			return (D_AMPERSAND);
		break;
	default : break;
	}
	return (0);
}

node_t *parse_separators(node_t *node, char *buffer, int *i)
{
	static int j = 0;
	static int n = 2;
	separator_type_t separator = 0;

	j = (*i == 0) ? 0 : j;
	n = (*i == 0) ? 2 : n;
	separator = is_separator(buffer, i, node);
	if (separator != 0) {
		if (node->next[n - 2]->buffer != NULL) {
			node->next = realloc_node(node->next, n++, node->quote, node->separator);
			node->next[n - 3]->separator = separator;
		}
		if (node->next == NULL)
			return (NULL);
		j = 0;
	} else {
		if ((node->next[n - 2]->buffer = \
		realloc(node->next[n - 2]->buffer, j + 2)) == NULL)
			return (NULL);
		node->next[n - 2]->buffer[j + 1] = '\0';
		node->next[n - 2]->buffer[j++] = buffer[*i];
	}
	return (node);
}

node_t *search_separators(node_t *node)
{
	node->next = realloc_node(node->next, 1, node->quote, node->separator);
	if (node->next == NULL)
		return (NULL);
	for (int i = 0; node->buffer[i] != '\0'; i++) {
		node = parse_separators(node, node->buffer, &i);
		if (node == NULL)
			return (NULL);
	}
	return (node);
}

node_t *parse_split(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		node->next[i] = search_separators(node->next[i]);
		if (node->next[i] == NULL)
			return (NULL);
	}
	return (parse_parentheses(node));
}