/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions to find and replace variables
*/

#include "my.h"
#include "parsing.h"
#include <stdlib.h>
#include <string.h>

char *fill_var(char *buffer, char *new_var_content, int i, size_t total_len)
{
	int tmp = i;

	for (; buffer[i]; i++)
		buffer[i + total_len + 1] = buffer[i];
	i = tmp;
	total_len += tmp;
	for (int j = 0; (size_t)i < total_len && new_var_content[j]; j++) {
		buffer[i] = new_var_content[j];
		i++;
	}
	return (buffer);
}

char *replace_var(char *buffer, char *new_var_content, char *new_var_name, \
int i)
{
	size_t buf_len = 0;
	size_t total_len = 0;
	size_t len_to_replace = 0;

	if (buffer == NULL || new_var_content == NULL || new_var_name == NULL)
		return (NULL);
	buf_len = strlen(buffer);
	total_len = strlen(new_var_content);
	len_to_replace = strlen(new_var_name) + 1;
	for (size_t size = 0; !(i + len_to_replace + size) \
	|| buffer[i + len_to_replace + size - 1]; size++) {
		buffer[i + size] = buffer[i + len_to_replace + size];
		if (!buffer[i + size])
			break;
	}
	if ((buffer = realloc(buffer, \
	sizeof(char) * (buf_len + total_len - len_to_replace + 1))) == NULL)
		return (NULL);
	buffer[buf_len + total_len - len_to_replace] = '\0';
	return (fill_var(buffer, new_var_content, i, total_len));
}