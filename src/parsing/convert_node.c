/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"
#include <string.h>

comm_t *apply_separator(comm_t *comm, node_t *node[2], int *comm_index, separator_type_t separator)
{
	comm_t *new_comm = NULL;
	int new_index = 1;

	node[0]->buffer = clear_str(node[0]->buffer);
	for (int i = 0; node[0]->buffer[i] != '\0'; i++)
		if (node[0]->buffer[i] == ' ' && separator >= S_ARROW_LEFT \
		&& separator <= D_ARROW_RIGHT) {
			comm->argv = parse_argv(comm->argv, node[0], comm_index, i);
			node[0]->buffer[i] = '\0';
			break;
		}
	if (separator <= S_AMPERSAND) {
		comm->separator = separator - 1;
	} else if (separator == S_PIPE) {
		new_comm = init_comm();
		comm->pipe[OUT] = init_pipe(comm, new_comm);
		comm->pipe[OUT]->output = fill_comm(comm->pipe[OUT]->output, node[1], &new_index);
	} else {
		comm->red[separator - 6] = init_redir();
		comm->red[separator - 6]->target = strdup(node[0]->buffer);
	}
	return (comm);
}

char **parse_argv(char **argv, node_t *node, int *comm_index, int index)
{
	int word_start = index;
	int i;

	node->buffer = clear_str(node->buffer);
	for (i = index; node->buffer[i] != '\0'; i++) {
		if (node->buffer[i] == ' ') {
			argv = realloc(argv, sizeof(char*) * ((*comm_index) + 2));
			argv[(*comm_index) + 1] = NULL;
			argv[(*comm_index)] = \
			strndup(&node->buffer[word_start], i - word_start);
			word_start = i + 1;
			(*comm_index)++;
		}
	}
	argv = realloc(argv, sizeof(char*) * ((*comm_index) + 2));
	argv[(*comm_index) + 1] = NULL;
	argv[(*comm_index)] = \
	strndup(&node->buffer[word_start], i - word_start);
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
	separator_type_t separator;

	i = (*node_index == 0) ? 0 : i;
	j = (*node_index == 0) ? 0 : j;
	k = (*node_index == 0) ? 0 : k;
	for (; node->next[i] != NULL && (j == 0 || node->next[i]->next[j - 1]->separator == 0) && (k == 0 || node->next[i]->next[j]->next[k - 1]->separator == 0); (*node_index)++) {
		if (node->next[i]->next[j] != NULL && node->next[i]->next[j]->next[k] != NULL)
			comm = convert_param(comm, \
			node->next[i]->next[j]->next[k++], &comm_index);
		if (node->next[i]->next[j] == NULL) {
			j = 0;
			i++;
			continue;
		}
		if (node->next[i]->next[j]->next[k] == NULL) {
			k = 0;
			j++;
		}
		if (node->next[i]->next[j] == NULL) {
			j = 0;
			i++;
		}
	}
	while (node->next[i] != NULL && node->next[i]->next[j] != NULL && node->next[i]->next[j]->next[k] != NULL) {
		if (k > 0 && node->next[i]->next[j]->next[k - 1]->separator >= S_AMPERSAND) {
			separator = node->next[i]->next[j]->next[k - 1]->separator;
			node->next[i]->next[j]->next[k - 1]->separator = 0;
			comm = apply_separator(comm, \
			(node_t*[2]){node->next[i]->next[j]->next[k], node}, &comm_index, separator);
			k += (separator == S_PIPE) ? 0 : 1;
		} else if (j > 0 && node->next[i]->next[j - 1]->separator <= D_PIPE && node->next[i]->next[j - 1]->separator >= SEMICOLON) {
			separator = node->next[i]->next[j - 1]->separator;
			node->next[i]->next[j - 1]->separator = 0;
			comm = apply_separator(comm, \
			(node_t*[2]){node->next[i]->next[j], node}, &comm_index, separator);
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