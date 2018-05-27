/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions to find and replace aliases in input
*/

#include "my.h"
#include "parsing.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

char *replace_alias(char *buffer, char *alias, int index[2], \
size_t alias_len)
{
	size_t buf_len = strlen(buffer);
	size_t total_len = strlen(alias);
	int tmp = index[0];

	for (size_t i = 0; !(index[0] + alias_len + i) \
	|| buffer[index[0] + i + alias_len - 1]; i++) {
		buffer[index[0] + i] = buffer[index[0] + alias_len + i];
		if (!buffer[index[0] + i])
			break;
	}
	if (!(buffer = realloc\
	(buffer, sizeof(char) * (buf_len + total_len - alias_len + 1))))
		return (NULL);
	buffer[buf_len + total_len - alias_len] = '\0';
	for (; buffer[index[0]]; index[0]++)
		buffer[index[0] + total_len + 1] = buffer[index[0]];
	index[0] = tmp;
	total_len += tmp;
	return (fill_alias(buffer, alias, index, total_len));
}

char *check_alias_loop(alias_t *alias, char *buffer)
{
	int loop = 0;
	alias_t *first = alias;

	while (alias) {
		if (alias->loop == true)
			loop++;
		alias = alias->nav[NEXT];
	}
	alias = first;
	if (loop > 1) {
		dprintf(STDERR_FILENO, "Alias loop.\n");
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char *compare_aliases(char *buffer, char *word, alias_t *alias, int index[2])
{
	alias_t *first = alias;

	if (!word || word[0] == '\0')
		return (buffer);
	while (alias) {
		if (!strcmp(word, alias->name) && alias->loop == false) {
			buffer = replace_alias(buffer, alias->alias, index, \
			strlen(alias->name));
			alias->loop = true;
			alias = first;
		} else if (strcmp(word, alias->name)) {
			alias = alias->nav[NEXT];
		} else {
			return (check_alias_loop(first, buffer));
		}
	}
	return (buffer);
}

alias_t *reset_alias_loop(alias_t *alias)
{
	alias_t *first = alias;

	while (alias) {
		alias->loop = false;
		alias = alias->nav[NEXT];
	}
	alias = first;
	return (alias);
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