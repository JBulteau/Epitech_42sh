/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** pipeline parsing for 42sh
*/

#include "my.h"
#include "parsing.h"

separator_type_t check_arrow(char *buffer, int *i, \
separator_type_t arrow)
{
	if (buffer[(*i) + 1] == buffer[*i]) {
		(*i)++;
		return (arrow + 1);
	}
	return (arrow);
}

separator_type_t check_cmd_separator(char *buffer, int *i, node_t *node)
{
	if (node->quote != NONE)
		return (SUCCESS_RETURN);
	switch (buffer[*i]) {
	case '|' :
		if (*i < 1 || !is_cmd_separator(buffer[(*i) - 1]))
			return (S_PIPE);
		break;
	case '>' :
		if (*i < 1 || !is_cmd_separator(buffer[(*i) - 1]))
			return (check_arrow(buffer, i, S_ARROW_RIGHT));
		break;
	case '<' :
		if (*i < 1 || !is_cmd_separator(buffer[(*i) - 1]))
			return (check_arrow(buffer, i, S_ARROW_LEFT));
		break;
	case '&' :
		if (*i < 1 || !is_cmd_separator(buffer[(*i) - 1]))
			return (S_AMPERSAND);
	}
	return (SUCCESS_RETURN);
}

node_t *fill_cmd_separators(node_t *node, char *buffer, int *i)
{
	static int j = 0;
	static int n = 2;
	separator_type_t separator = 0;

	j = (*i == 0) ? 0 : j;
	n = (*i == 0) ? 2 : n;
	separator = check_cmd_separator(buffer, i, node);
	if (separator != 0) {
		if (node->next[n - 2]->buffer != NULL \
		&& node->next[n - 2]->fg == false) {
			node->next = realloc_node(node->next, n++, node->quote);
			node->next[n - 3]->separator = separator;
		}
		j = 0;
		if (separator == S_AMPERSAND && buffer[*i + 1] == '\0') {
			free_node(node->next[n - 2]);
			node->next[n - 2] = NULL;
		}
	} else {
		if ((node->next[n - 2]->buffer = \
		realloc(node->next[n - 2]->buffer, j + 2)) == NULL)
			return (NULL);
		node->next[n - 2]->buffer[j + 1] = '\0';
		node->next[n - 2]->buffer[j++] = buffer[*i];
	}
	return ((node->next == NULL) ? NULL : node);
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

node_t *parse_cmd_separators(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		node->next[i] = browse_sep_node(node->next[i]);
		if (node->next[i] == NULL)
			return (NULL);
	}
	return (node);
}