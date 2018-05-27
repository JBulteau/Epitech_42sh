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

comm_t *convert_param(comm_t *comm, node_t *node, int *comm_index, \
shell_t *shell)
{
	char *buffer = NULL;

	if (node->quote == NONE) {
		if (!(comm->argv = parse_argv(comm->argv, node, comm_index, 0)))
			return (NULL);
	} else if (node->quote == MAGIC) {
		buffer = get_magic(shell, strdup(node->buffer));
		free_array((void*)comm->argv);
		if ((comm->argv = strwordarr(buffer, " \t\n")) == NULL)
			return (NULL);
		free(buffer);
	} else {
		if ((comm->argv = realloc\
		(comm->argv, sizeof(char*) * ((*comm_index) + 2))) == NULL)
			return (NULL);
		comm->argv[(*comm_index)] = strdup(node->buffer);
		if (comm->argv[(*comm_index)] == NULL)
			return (NULL);
		comm->argv[(*comm_index)++ + 1] = NULL;
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

comm_t *fill_comm(comm_t *comm, node_t *node, int *node_index, shell_t *shell)
{
	static int index [3] = {0, 0, 0};
	static int recursive_lvl = 0;
	int comm_index = 0;

	for (int i = 0; i < 3; i++)
		index[i] = (*node_index == 0) ? 0 : index[i];
	recursive_lvl++;
	for (; is_valid_node(comm, node, index); (*node_index)++) {
		if (index_save(index, SAVE) == ERROR_RETURN)
			return (NULL);
		if (node->next[index[0]]->next[index[1]] \
		&& node->next[index[0]]->next[index[1]]->next[index[2]])
			comm = convert_param(comm, node->next[index[0]]->\
			next[index[1]]->next[index[2]++], &comm_index, shell);
		if (index_save(index, LOAD) == ERROR_RETURN)
			return (NULL);
		check_node(node, index);
	}
	recursive_lvl--;
	return (handle_separators(comm, node, (int[4])\
	{index[0], index[1], index[2], comm_index}, shell));
}

comm_t **convert_node(comm_t **comm, node_t *node, shell_t *shell)
{
	int node_index = 0;

	if (comm == NULL)
		return (NULL);
	for (int i = 0; comm[i] != NULL; i++) {
		comm[i] = fill_comm(comm[i], node, &node_index, shell);
		if (comm[i] == NULL) {
			free_comms(comm);
			return (NULL);
		}
	}
	return (comm);
}