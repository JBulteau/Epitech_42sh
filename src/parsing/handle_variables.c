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

char *replace_var(char *buffer, char *new_var_content, char *new_var_name, int i)
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
	buffer = realloc(buffer, sizeof(char) * (buf_len + total_len - len_to_replace + 1));
	if (buffer == NULL)
		return (NULL);
	buffer[buf_len + total_len - len_to_replace] = '\0';
	return (fill_var(buffer, new_var_content, i, total_len));
}

char *get_variable_name(char *buffer, char *new_var_name)
{
	int len;

	for (len = 0; buffer[len] && buffer[len] != '\t' \
	&& buffer[len] != ' '; len++);
	new_var_name = realloc(new_var_name, sizeof(char) * (len + 1));
	if (new_var_name == NULL)
		return (NULL);
	new_var_name = memset(new_var_name, 1, len + 1);
	new_var_name[len] = '\0';
	for (int i = 0; new_var_name[i]; i++)
		new_var_name[i] = buffer[i];
	return (new_var_name);
}

char *search_variables(char *buffer, shell_t *shell)
{
	char *new_var_name = NULL;
	char *new_var_content = NULL;

	if (!buffer)
		return (NULL);
	for (int i = 0; buffer[i]; i++) {
		if (buffer[i] == '$') {
			new_var_name = get_variable_name(&buffer[i + 1], new_var_name);
			new_var_content = get_var(shell->env, shell->vars, new_var_name);
			buffer = replace_var(buffer, new_var_content, new_var_name, i);
		}
	}
	return (buffer);
}

node_t *handle_variables(node_t *node, shell_t *shell)
{
	for (int i = 0; node && node->next[i]; i++) {
		if ((node->next[i]->quote == NONE \
		|| node->next[i]->quote == DOUBLE) && node->next[i]->buffer)
			node->next[i]->buffer = \
			search_variables(node->next[i]->buffer, shell);
	}
	return (node);
}