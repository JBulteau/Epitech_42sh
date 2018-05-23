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

node_t *attribute_cmd_separator(node_t *node, int index[], int *i, char *buffer)
{
	if (node->next[index[1] - 2]->buffer && !node->next[index[1] - 2]->fg) {
		node->next = realloc_node(node->next, index[1]++, node->quote);
		node->next[index[1] - 3]->separator = index[2];
	}
	index[0] = 0;
	if (index[2] == S_AMPERSAND && buffer[*i + 1] == '\0') {
		free_node(node->next[index[1] - 2]);
		node->next[index[1] - 2] = NULL;
	}
	return (node);
}

node_t *fill_cmd_separators(node_t *node, char *buffer, int *i)
{
	static int index[3] = {0, 2, 0};

	index[0] = (*i == 0) ? 0 : index[0];
	index[1] = (*i == 0) ? 2 : index[1];
	index[2] = check_cmd_separator(buffer, i, node);
	if (index[2]) {
		node = attribute_cmd_separator(node, index, i, buffer);
	} else {
		if ((node->next[index[1] - 2]->buffer = realloc\
		(node->next[index[1] - 2]->buffer, index[0] + 2)) == NULL)
			return (NULL);
		node->next[index[1] - 2]->buffer[index[0] + 1] = '\0';
		node->next[index[1] - 2]->buffer[index[0]++] = buffer[*i];
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