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
	return (buffer);
}

char *fill_word(char *buffer, char *word, int index)
{
	for (int i = 0; buffer[index] != ' ' && buffer[index] != '\t' \
	&& buffer[index] != '\0'; i++) {
		word[i] = buffer[index];
		index++;
	}
	return (word);
}

char *isolate_word(char *buffer, alias_t *alias)
{
	char *word = malloc(sizeof(char) * (strlen(buffer) + 1));
	int index[2] = {0, 0};

	if (!word)
		return (buffer);
	buffer = clear_str(buffer);
	for (; buffer && (!index[1] || buffer[index[1] - 1]); index[1]++) {
		word = memset(word, '\0', strlen(buffer) + 1);
		if (is_first_arg(buffer, index[1])) {
			index[0] = index[1];
			word = fill_word(buffer, word, index[1]);
			buffer = compare_aliases(buffer, word, alias, index);
		}
		word = realloc(word, sizeof(char) * (strlen(buffer) + 1));
		if (word == NULL)
			return (buffer);
	}
	free(word);
	return (buffer);
}

int is_first_arg(char *buffer, int index)
{
	return ((index == 0) || (index == 1 && (buffer[0] == '&' \
	|| buffer[0] == '|' || buffer[0] == ';')) || (index == 2 \
	&& (buffer[0] == '|' || buffer[0] == ';' || buffer[0] == '&') \
	&& (buffer[1] == ' ' || buffer[1] == '\t' || buffer[1] == '&' \
	|| buffer[1] == '|')));
}

char *search_aliases(char *buffer, alias_t *alias)
{
	if (!buffer)
		return (NULL);
	buffer = isolate_word(buffer, alias);
	alias = reset_alias_loop(alias);
	return (buffer);
}