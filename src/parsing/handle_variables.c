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
#include <stdio.h>

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

char *get_last_return_value(char *new_var_content, shell_t *shell)
{
	char tmp[256] = {'\0'};

	sprintf(tmp, "%i", shell->return_value);
	new_var_content = strdup(tmp);
	return (new_var_content);
}

char *handle_new_variable(char *buffer, shell_t *shell, int i)
{
	char *new_var_name = NULL;
	char *new_var_content = NULL;

	new_var_name = get_variable_name(&buffer[i + 1], new_var_name);
	if (new_var_name && new_var_name[0] == '?' && new_var_name[1] == '\0') {
		new_var_content = get_last_return_value(new_var_content, shell);
	} else {
		new_var_content = \
		get_var(shell->env, shell->vars, new_var_name);
	}
	buffer = replace_var(buffer, new_var_content, new_var_name, i);
	free(new_var_name);
	free(new_var_content);
	return (buffer);
}

char *search_variables(char *buffer, shell_t *shell)
{
	if (!buffer)
		return (NULL);
	for (int i = 0; buffer && buffer[i]; i++) {
		if (buffer[i] == '$') {
			buffer = handle_new_variable(buffer, shell, i);
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