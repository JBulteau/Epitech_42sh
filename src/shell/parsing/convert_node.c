/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

comm_t *apply_separator(comm_t *comm, node_t *node, int *comm_index)
{
	comm_t *new_comm = NULL;

	node->buffer = clear_str(node->buffer);
	for (int i = 0; node->buffer[i] != '\0'; i++)
		if (node->buffer[i] == ' ' && node->separator >= S_ARROW_LEFT \
		&& node->separator <= D_ARROW_RIGHT) {
			comm->argv = parse_argv(comm->argv, node, comm_index);
			node->buffer[i] = '\0';
			break;
		}
	if (node->separator <= S_AMPERSAND) {
		comm->separator = node->separator - 1;
	} else if (node->separator == S_PIPE) {
		new_comm = init_comm();
		comm->pipe[IN] = init_pipe(comm, new_comm);
	} else {
		comm->red[node->separator - 6] = init_redir();
		comm->red[node->separator - 6]->target = strdup(node->buffer);
	}
	return (comm);
}

char **parse_argv(char **argv, node_t *node, int *comm_index)
{
	int word_start = 0;

	node->buffer = clear_str(node->buffer);
	for (int i = 0; node->buffer[i] != '\0'; i++) {
		if (node->buffer[i] == ' ') {
			argv = realloc(argv, sizeof(char*) * (*comm_index) + 2);
			argv[(*comm_index) + 1] = NULL;
			argv[(*comm_index)] = \
			strndup(&node->buffer[word_start], i - word_start);
			word_start = i + 1;
			(*comm_index)++;
		}
	}
	return (argv);
}

comm_t *convert_param(comm_t *comm, node_t *node, int *comm_index)
{
	if (node->quote == NONE) {
		comm->argv = parse_argv(comm->argv, node, comm_index);
		if (comm->argv == NULL)
			return (NULL);
	} else {
		comm->argv[(*comm_index)] = strdup(node->buffer);
		(*comm_index)++;
	}
	return (comm);
}

comm_t *fill_comm(comm_t *comm, node_t *node, int *node_index)
{
	static int i = 0;
	static int j = 0;
	static int k = 0;
	int comm_index = 0;

	i = (*node_index == 0) ? 0 : i;
	j = (*node_index == 0) ? 0 : j;
	k = (*node_index == 0) ? 0 : k;
	for (; node->next[i] != NULL \
	&& node->next[i]->next[j]->next[k]->separator == 0; (*node_index)++) {
		comm = convert_param(comm, \
		node->next[i]->next[j]->next[k++], &comm_index);
		k = (node->next[i]->next[j]->next[k] == NULL) ? 0 : k;
		j += (node->next[i]->next[j]->next[k] == NULL) ? 1 : 0;
		j = (node->next[i]->next[j] == NULL) ? 0 : j;
		i += (node->next[i]->next[j] == NULL) ? 1 : 0;
	}
	if (node->next[i] != NULL)
		comm = apply_separator(comm, \
		node->next[i]->next[j]->next[k], &comm_index);
	return (comm);
}

comm_t **convert_node(comm_t **comm, node_t *node)
{
	int node_index = 0;

	for (int i = 0; comm[i] != NULL; i++) {
		comm[i] = fill_comm(comm[i], node, &node_index);
		if (comm[i] == NULL) {
			free_comms(comm);
			return (NULL);
		}
	}
	return (comm);
}