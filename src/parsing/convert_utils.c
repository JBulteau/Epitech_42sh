/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions for node to interpretable structure conversion
*/

#include "my.h"
#include "parsing.h"

int is_separator_char(char c)
{
	return (is_cmd_separator(c) || c == ';');
}

int index_save(int index[5], int status)
{
	static int **index_array;

	if (status == SAVE) {
		index_array = realloc(index_array, sizeof(int[3]) * index[3]);
		if (index_array == NULL)
			return (ERROR_RETURN);
		index_array[index[3] - 1] = malloc(sizeof(int) * 3);
		if (index_array[index[3] - 1] == NULL)
			return (ERROR_RETURN);
		index_array[index[3] - 1][0] = index[0];
		index_array[index[3] - 1][1] = index[1];
		index_array[index[3] - 1][2] = index[2] + 1;
	} else {
		for (int i = 0; i < 3; i++) {
			index[i] = index_array[index[3] - 1][i];
		}
		free(index_array[index[3] - 1]);
		index_array = \
		realloc(index_array, sizeof(int[3]) * (index[3] - 1));
	}
	return (SUCCESS_RETURN);
}

int is_valid_node(comm_t *comm, node_t *node, int index[3])
{
	return (comm && node->next[index[0]] && (index[1] == 0 || \
	node->next[index[0]]->next[index[1] - 1]->separator == 0) \
	&& (index[2] == 0 || node->next[index[0]]->next[index[1]]->\
	next[index[2] - 1]->separator == 0));
}