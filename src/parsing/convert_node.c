/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

char **parse_argv(char **argv, node_t *node, int *comm_index, int index)
{
	int word_start = index;
	int i;

	node->buffer = clear_str(node->buffer);
	for (i = index; node->buffer \
	&& (i == 0 || node->buffer[i - 1] != '\0'); i++) {
		if (node->buffer[i] == '\0' || node->buffer[i] == ' ') {
			argv = \
			realloc(argv, sizeof(char*) * ((*comm_index) + 2));
			argv[(*comm_index) + 1] = NULL;
			argv[(*comm_index)] = \
			strndup(&node->buffer[word_start], i - word_start);
			word_start = i + 1;
			(*comm_index)++;
		}
		if ((node->buffer[i] == '\0' || node->buffer[i] == ' ') \
		&& argv[(*comm_index) - 1] == NULL)
			return (NULL);
	}
	return (argv);
}

comm_t *convert_param(comm_t *comm, node_t *node, int *comm_index)
{
	if (node->quote == NONE) {
		comm->argv = parse_argv(comm->argv, node, comm_index, 0);
		if (comm->argv == NULL)
			return (NULL);
	} else {
		comm->argv = \
		realloc(comm->argv, sizeof(char*) * ((*comm_index) + 2));
		if (comm->argv == NULL)
			return (NULL);
		comm->argv[(*comm_index)] = strdup(node->buffer);
		if (comm->argv[(*comm_index)] == NULL)
			return (NULL);
		comm->argv[(*comm_index) + 1] = NULL;
		(*comm_index)++;
	}
	return (comm);
}

void check_node(node_t *node, int index[3])
{
	if (node->next[index[0]]->next[index[1]] == NULL) {
		index[1] = 0;
		index[0]++;
		return;
	}
	if (node->next[index[0]]->next[index[1]]->\
	next[index[2]] == NULL) {
		index[2] = 0;
		index[1]++;
	}
	if (node->next[index[0]]->next[index[1]] == NULL) {
		index[1] = 0;
		index[0]++;
	}
}

comm_t *fill_comm(comm_t *comm, node_t *node, int *node_index)
{
	static int index[3] = {0, 0, 0};
	int comm_index = 0;

	index[0] = (*node_index == 0) ? 0 : index[0];
	index[1] = (*node_index == 0) ? 0 : index[1];
	index[2] = (*node_index == 0) ? 0 : index[2];
	for (; comm && node->next[index[0]] && (index[1] == 0 || \
	node->next[index[0]]->next[index[1] - 1]->separator == 0) \
	&& (index[2] == 0 || node->next[index[0]]->next[index[1]]->\
	next[index[2] - 1]->separator == 0); (*node_index)++) {
		if (node->next[index[0]]->next[index[1]] \
		&& node->next[index[0]]->next[index[1]]->next[index[2]]) {
			comm = convert_param(comm, node->next[index[0]]->\
			next[index[1]]->next[index[2]++], &comm_index);
		}
		check_node(node, index);
	}
	return (handle_separators(comm, node, index, &comm_index));
}

comm_t **convert_node(comm_t **comm, node_t *node)
{
	int node_index = 0;

	if (comm == NULL)
		return (NULL);
	for (int i = 0; comm[i] != NULL; i++) {
		comm[i] = fill_comm(comm[i], node, &node_index);
		if (comm[i] == NULL) {
			free_comms(comm);
			return (NULL);
		}
	}
	return (comm);
}