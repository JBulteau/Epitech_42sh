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
	if (separator <= D_PIPE) {
		comm->separator = separator - 1;
		if (separator > SEMICOLON)
			comm->next = fill_comm(init_comm(), node[1], new_index);
	} else if (separator == S_PIPE) {
		comm->pipe[OUT] = init_pipe(comm, init_comm());
		comm->pipe[OUT]->output = \
		fill_comm(comm->pipe[OUT]->output, node[1], new_index);
	} else
		if (separator != S_AMPERSAND) {
			comm->red[separator - 6] = init_redir();
			comm->red[separator - 6]->target = \
			strdup(node[0]->buffer);
		} else
			comm->bg = true;
	if (REDIR(separator) && comm->red[separator - 6] \
	&& comm->red[separator - 6]->target == NULL)
		return (NULL);
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

comm_t *handle_basic_separators(comm_t *comm, node_t *node, int idx[3], \
int *comm_index)
{
	separator_type_t sep;

	sep = node->next[idx[0]]->next[idx[1] - 1]->separator;
	node->next[idx[0]]->next[idx[1] - 1]->separator = 0;
	comm = apply_separator(comm, (node_t*[2])\
	{node->next[idx[0]]->next[idx[1]], node}, comm_index, sep);
	return (comm);
}

comm_t *handle_advanced_separators(comm_t *comm, node_t *node, int idx[3], \
int *comm_index)
{
	separator_type_t sep;

	sep = node->next[idx[0]]->next[idx[1]]->next[idx[2] - 1]->separator;
	node->next[idx[0]]->next[idx[1]]->next[idx[2] - 1]->separator = 0;
	comm = apply_separator(comm, (node_t*[2]){node->\
	next[idx[0]]->next[idx[1]]->next[idx[2]], node}, comm_index, sep);
	idx[2] += (sep == S_PIPE || sep == S_AMPERSAND) ? 0 : 1;
	return (comm);
}

comm_t *handle_separators(comm_t *comm, node_t *node, int idx[3], \
int *comm_index)
{
	while (comm && node->next[idx[0]] && node->next[idx[0]]->next[idx[1]] \
	&& node->next[idx[0]]->next[idx[1]]->next[idx[2]]) {
		if (idx[2] > 0 && node->next[idx[0]]->next[idx[1]]->\
		next[idx[2] - 1]->separator >= S_AMPERSAND) {
			comm = \
			handle_advanced_separators(comm, node, idx, comm_index);
		} else if (idx[1] > 0 && node->next[idx[0]]->\
		next[idx[1] - 1]->separator <= D_PIPE && node->\
		next[idx[0]]->next[idx[1] - 1]->separator >= SEMICOLON) {
			comm = \
			handle_basic_separators(comm, node, idx, comm_index);
			break;
		} else {
			break;
		}
	}
	return (comm);
}