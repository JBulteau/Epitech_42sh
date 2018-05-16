/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** globbing parsing for 42sh
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

node_t *replace_glob(node_t *node, glob_t pglob, int j, size_t len)
{
	int total_len = 0;
	int buf_len = strlen(node->buffer);
	int tmp = j;
	int k = 0;
	int n = 0;

	for (size_t i = 0; i < pglob.gl_pathc; i++) {
		total_len += strlen(pglob.gl_pathv[i]) + 1;
	}
	node->buffer = realloc(node->buffer, sizeof(char) * (buf_len + total_len - len));
	if (node->buffer == NULL)
		return (NULL);
	for (size_t i = 0; j + i + len <= buf_len && i <= len + 1; i++)
		node->buffer[j + i - 1] = node->buffer[j + len + i];
	for (; node->buffer[j - 1] != '\0'; j++)
		node->buffer[j + total_len] = node->buffer[j];
	for (j = tmp; j < tmp + total_len && n < pglob.gl_pathc; j++) {
		if (pglob.gl_pathv[n][k] != '\0') {
			node->buffer[j] = pglob.gl_pathv[n][k];
			k++;
		} else {
			node->buffer[j] = ' ';
			n++;
			k = 0;
		}
	}
	return (node);
}

node_t *isolate_glob(node_t *node, int i)
{
	char *tmp = NULL;
	size_t len = 0;
	int j = i;
	glob_t pglob;

	for (; i >= 0 && node->buffer[i] != ' ' && node->buffer[i] != '\t'; i--)
		len++;
	for (; node->buffer[j] != '\0' && node->buffer[j] != ' ' && node->buffer[j] != '\t'; j++)
		len++;
	tmp = malloc(sizeof(char) * len);
	if (tmp == NULL)
		return (NULL);
	strncpy(tmp, &node->buffer[i + 1], len - 1);
	tmp[len - 1] = '\0';
	if (glob(tmp, GLOB_TILDE_CHECK, NULL, &pglob) != 0)
		return (NULL);
	len = strlen(tmp);
	free(tmp);
	node = replace_glob(node, pglob, i + 1, len);
	globfree(&pglob);
	return (node);
}

node_t *check_globbing(node_t *node)
{
	for (int i = 0; node->buffer[i] != '\0'; i++) {
		if (node->buffer[i] == '*') {
			node = isolate_glob(node, i);
		}
		if (node->buffer == NULL)
			return (NULL);
	}
	return (node);
}

static node_t *browse_node(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		if (node->next[i]->quote == NONE)
			node->next[i] = \
			check_globbing(node->next[i]);
		if (node->next[i] == NULL)
			return (NULL);
	}
	return (node);
}

node_t *parse_globbing(node_t *node)
{
	for (int i = 0; node->next[i] != NULL; i++) {
		node->next[i] = browse_node(node->next[i]);
		if (node->next[i] == NULL)
			return (NULL);
	}
	return (node);
}