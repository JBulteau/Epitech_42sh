/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions to find and replace aliases in input
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

int is_first_arg(char c)
{
	return (c == '|' || c == '&' || c == ';');
}

node_t *handle_aliases(node_t *node, shell_t *shell)
{
	for (int i = 0; node && node->next[i]; i++) {
		if (node->next[i]->quote == NONE && node->next[i]->buffer)
			node->next[i]->buffer = \
			search_aliases(node->next[i]->buffer, shell->aliases);
	}
	return (node);
}