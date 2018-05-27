/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

comm_t *set_separator(comm_t *comm, node_t *node[2], int new_index[2], \
shell_t *shell)
{
	if (new_index[0] <= D_PIPE) {
		comm = simple_separators(comm, node, new_index, shell);
	} else if (new_index[0] == S_PIPE) {
		comm = simple_pipe(comm, node, new_index, shell);
	} else {
		if (new_index[0] != S_AMPERSAND) {
			comm = redir(comm, node, new_index);
		} else {
			comm = ampersand(comm, new_index);
		}
	}
	return (comm);
}

comm_t *apply_separator(comm_t *comm, node_t *node[2], int comm_index[2], \
shell_t *shell)
{
	int new_index = 1;

	node[0]->buffer = clear_str(node[0]->buffer);
	for (int i = 0; node[0]->buffer && node[0]->buffer[i] != '\0'; i++) {
		if (node[0]->buffer[i] == ' ' && comm_index[0] >= S_ARROW_LEFT \
		&& comm_index[0] <= D_ARROW_RIGHT) {
			comm->argv = \
			parse_argv(comm->argv, node[0], &comm_index[1], i);
			node[0]->buffer[i] = '\0';
			break;
		}
	}
	comm = set_separator(comm, node, (int[2]){comm_index[0], new_index}, shell);
	return (comm);
}

comm_t *handle_basic_separators(comm_t *comm, node_t *node, int idx[4], \
shell_t *shell)
{
	separator_type_t sep;

	sep = node->next[idx[0]]->next[idx[1] - 1]->separator;
	node->next[idx[0]]->next[idx[1] - 1]->separator = 0;
	comm = apply_separator(comm, (node_t*[2])\
	{node->next[idx[0]]->next[idx[1]], node}, (int[2]){sep, idx[3]}, shell);
	return (comm);
}

comm_t *handle_advanced_separators(comm_t *comm, node_t *node, int idx[4], \
shell_t *shell)
{
	separator_type_t sep;

	sep = node->next[idx[0]]->next[idx[1]]->next[idx[2] - 1]->separator;
	node->next[idx[0]]->next[idx[1]]->next[idx[2] - 1]->separator = 0;
	comm = apply_separator(comm, (node_t*[2]){node->\
	next[idx[0]]->next[idx[1]]->next[idx[2]], node}, (int[2]){sep, idx[3]}, shell);
	idx[2] += (sep == S_PIPE || sep == S_AMPERSAND) ? 0 : 1;
	return (comm);
}

comm_t *handle_separators(comm_t *comm, node_t *node, int idx[4], \
shell_t *shell)
{
	while (comm && node->next[idx[0]] && node->next[idx[0]]->next[idx[1]] \
	&& node->next[idx[0]]->next[idx[1]]->next[idx[2]]) {
		if (idx[2] > 0 && node->next[idx[0]]->next[idx[1]]->\
		next[idx[2] - 1]->separator >= S_AMPERSAND) {
			comm = \
			handle_advanced_separators(comm, node, (int[4]){idx[0], idx[1], idx[2], idx[3]}, shell);
		} else if (idx[1] > 0 && node->next[idx[0]]->\
		next[idx[1] - 1]->separator <= D_PIPE && node->\
		next[idx[0]]->next[idx[1] - 1]->separator >= SEMICOLON) {
			comm = \
			handle_basic_separators(comm, node, (int[4]){idx[0], idx[1], idx[2], idx[3]}, shell);
			break;
		} else {
			break;
		}
	}
	return (comm);
}
