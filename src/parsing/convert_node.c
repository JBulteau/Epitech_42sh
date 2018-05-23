/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

comm_t *set_separator(comm_t *comm, node_t *node[2], \
separator_type_t separator, int *new_index)
{
	comm_t *new_comm = NULL;

	if (separator <= D_PIPE) {
		comm->separator = separator - 1;
	} else if (separator == S_PIPE) {
		new_comm = init_comm();
		comm->pipe[OUT] = init_pipe(comm, new_comm);
		comm->pipe[OUT]->output = \
		fill_comm(comm->pipe[OUT]->output, node[1], new_index);
	} else {
		if (separator == S_AMPERSAND) {
			comm->fg = true;
		} else {
			comm->red[separator - 6] = init_redir();
			comm->red[separator - 6]->target = \
			strdup(node[0]->buffer);
			if (comm->red[separator - 6]->target == NULL)
				return (NULL);
		}
	}
	return (comm);
}

comm_t *apply_separator(comm_t *comm, node_t *node[2], int *comm_index, \
separator_type_t separator)
{
	int new_index = 1;

	node[0]->buffer = clear_str(node[0]->buffer);
	for (int i = 0; node[0]->buffer && node[0]->buffer[i] != '\0'; i++) {
		if (node[0]->buffer[i] == ' ' && separator >= S_ARROW_LEFT \
		&& separator <= D_ARROW_RIGHT) {
			comm->argv = \
			parse_argv(comm->argv, node[0], comm_index, i);
			node[0]->buffer[i] = '\0';
			break;
		}
	}
	comm = set_separator(comm, node, separator, &new_index);
	return (comm);
}

char **parse_argv(char **argv, node_t *node, int *comm_index, int index)
{
	int word_start = index;
	int i;

	node->buffer = clear_str(node->buffer);
	for (i = index; node->buffer && node->buffer[i] != '\0'; i++) {
		if (node->buffer[i] == ' ') {
			argv = \
			realloc(argv, sizeof(char*) * ((*comm_index) + 2));
			argv[(*comm_index) + 1] = NULL;
			argv[(*comm_index)] = \
			strndup(&node->buffer[word_start], i - word_start);
			word_start = i + 1;
			(*comm_index)++;
		}
		if (node->buffer[i] == ' ' && argv[(*comm_index) - 1] == NULL)
			return (NULL);
	}
	argv = realloc(argv, sizeof(char*) * ((*comm_index) + 2));
	if (argv == NULL)
		return (NULL);
	argv[(*comm_index) + 1] = NULL;
	argv[(*comm_index)] = \
	strndup(&node->buffer[word_start], i - word_start);
	if (argv[(*comm_index)] == NULL)
		return (NULL);
	word_start = i + 1;
	(*comm_index)++;
	return (argv);
}

comm_t *convert_param(comm_t *comm, node_t *node, int *comm_index)
{
	if (node->quote == NONE) {
		comm->argv = parse_argv(comm->argv, node, comm_index, 0);
		if (comm->argv == NULL)
			return (NULL);
	} else {
		comm->argv[(*comm_index)] = strdup(node->buffer);
		if (comm->argv[(*comm_index)] == NULL)
			return (NULL);
		(*comm_index)++;
	}
	return (comm);
}

comm_t *fill_comm(comm_t *comm, node_t *node, int *node_index)
{
	static int index[3] = {0, 0, 0};
	int comm_index = 0;
	separator_type_t sep;

	index[0] = (*node_index == 0) ? 0 : index[0];
	index[1] = (*node_index == 0) ? 0 : index[1];
	index[2] = (*node_index == 0) ? 0 : index[2];
	for (; node->next[index[0]] && (index[1] == 0 || \
	node->next[index[0]]->next[index[1] - 1]->separator == 0) \
	&& (index[2] == 0 || node->next[index[0]]->next[index[1]]->\
	next[index[2] - 1]->separator == 0); (*node_index)++) {
		if (node->next[index[0]]->next[index[1]] \
		&& node->next[index[0]]->next[index[1]]->next[index[2]])
			comm = convert_param(comm, node->next[index[0]]->\
			next[index[1]]->next[index[2]++], &comm_index);
		if (comm == NULL)
			return (NULL);
		if (node->next[index[0]]->next[index[1]] == NULL) {
			index[1] = 0;
			index[0]++;
			continue;
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
	while (node->next[index[0]] && node->next[index[0]]->next[index[1]] \
	&& node->next[index[0]]->next[index[1]]->next[index[2]]) {
		if (index[2] > 0 && node->next[index[0]]->next[index[1]]->\
		next[index[2] - 1]->separator >= S_AMPERSAND) {
			sep = node->next[index[0]]->next[index[1]]->\
			next[index[2] - 1]->separator;
			node->next[index[0]]->next[index[1]]->\
			next[index[2] - 1]->separator = 0;
			comm = apply_separator(comm, (node_t*[2]){node->\
			next[index[0]]->next[index[1]]->next[index[2]], node}, \
			&comm_index, sep);
			if (comm == NULL)
				return (NULL);
			index[2] += (sep == S_PIPE || sep == S_AMPERSAND) ? 0 : 1;
		} else if (index[1] > 0 && node->next[index[0]]->\
		next[index[1] - 1]->separator <= D_PIPE && node->\
		next[index[0]]->next[index[1] - 1]->separator >= SEMICOLON) {
			sep = \
			node->next[index[0]]->next[index[1] - 1]->separator;
			node->next[index[0]]->next[index[1] - 1]->separator = 0;
			comm = apply_separator(comm, (node_t*[2])\
			{node->next[index[0]]->next[index[1]], node}, \
			&comm_index, sep);
			if (comm == NULL)
				return (NULL);
			break;
		} else {
			break;
		}
	}
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