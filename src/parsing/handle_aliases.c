/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions to find and replace aliases in input
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

char *fill_alias(char *buffer, char *alias, int index[2], size_t total_len)
{
	int i = 0;

	for (; (size_t)index[0] < total_len && alias[i]; index[0]++) {
		buffer[index[0]] = alias[i];
		i++;
	}
	index[0]++;
	index[1] = index[0];
	return (buffer);
}

char *replace_alias(char *buffer, char *alias, int index[2], size_t alias_len)
{
	size_t buf_len = strlen(buffer);
	size_t total_len = strlen(alias);
	int tmp = index[0];

	if (!(buffer = \
	realloc(buffer, sizeof(char) * (buf_len + total_len - alias_len + 1))))
		return (NULL);
	for (size_t i = 0; !(index[0] + 1 + alias_len - 1) \
	|| buffer[index[0] + i + alias_len - 1]; i++) {
		buffer[index[0] + i] = buffer[index[0] + alias_len + 1];
		if (!buffer[index[0] + i])
			break;
	}
	buffer[buf_len + total_len - alias_len] = '\0';
	for (; buffer[index[0]]; index[0]++)
		buffer[index[0] + total_len + 1] = buffer[index[0]];
	index[0] = tmp;
	total_len += tmp;
	return (fill_alias(buffer, alias, index, total_len));
}

char *compare_aliases(char *buffer, char *word, alias_t *alias, int index[2])
{
	if (!strcmp(word, alias->name)) {
		buffer = replace_alias(buffer, alias->alias, index, strlen(alias->name));
	}
	return (buffer);
}

char *isolate_word(char *buffer, alias_t *alias)
{
	char *word = malloc(sizeof(char) * strlen(buffer));
	int index[2] = {0, 0};

	if (!word)
		return (buffer);
	buffer = clear_str(buffer);
	word = memset(word, '\0', strlen(buffer));
	for (; !index[1] || buffer[index[1] - 1]; index[1]++) {
		if (buffer[index[1]] != ' ' && buffer[index[1]] != '\t' \
		&& buffer[index[1]] != '\0') {
			word[index[1]] = buffer[index[1]];
		} else {
			buffer = compare_aliases(buffer, word, alias, index);
			word = memset(word, '\0', strlen(buffer));
		}
	}
	return (buffer);
}

char *search_aliases(char *buffer, alias_t *alias)
{
	alias_t *first = alias;

	if (!buffer)
		return (NULL);
	while (alias) {
		buffer = isolate_word(buffer, alias);
		alias = alias->nav[NEXT];
	}
	alias = first;
	return (buffer);
}

node_t *handle_aliases(node_t *node, shell_t *shell)
{
	int index [3] = {0, 0, 0};

	for (; node && node->next[index[0]] \
	&& node->next[index[0]]->next[index[1]] \
	&& node->next[index[0]]->next[index[1]]->next[index[2]]; index[2]++) {
		if (!node->next[index[0]]->next[index[1]]->next[index[2]]) {
			index[2] = 0;
			index[1]++;
		}
		if (!node->next[index[0]]->next[index[1]]) {
			index[1] = 0;
			index[0]++;
		}
		node->next[index[0]]->next[index[1]]->next[index[2]]->buffer = \
		search_aliases(node->next[index[0]]->next[index[1]]->\
		next[index[2]]->buffer, shell->aliases);
	}
	return (node);
}