/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** init_comm_array before converting
*/

#include "my.h"
#include "parsing.h"
#include <stdlib.h>

int get_nb_comm(node_t *node)
{
	int i = 0;
	int j = 0;
	int nb_comm = 1;

	for (;node->next[i] != NULL; j++) {
		if (node->next[i]->next[j] == NULL) {
			j = 0;
			i++;
		}
		if (node->next[i] \
		&& node->next[i]->next[j]->separator == SEMICOLON)
			nb_comm++;
	}
	return (nb_comm);
}

comm_t **init_comm_array(comm_t **comm, node_t *node)
{
	int nb_comm = 0;

	if (!node)
		return (NULL);
	nb_comm = get_nb_comm(node);
	comm = malloc(sizeof(comm_t*) * (nb_comm + 1));
	if (comm == NULL)
		return (NULL);
	for (int i = 0; i < nb_comm; i++) {
		comm[i] = init_comm();
		if (comm[i] == NULL) {
			free_comms(comm);
			return (NULL);
		}
	}
	comm[nb_comm] = NULL;
	return (comm);
}