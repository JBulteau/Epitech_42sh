/*
** EPITECH PROJECT, 2017
** disp_modif.c
** File description:
** Display did you mean
*/

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

void disp_comm(comm_t *comm)
{
	for (int i = 0; comm->argv[i]; i++)
		printf("%s ", comm->argv[i]);
	if (comm->separator == THEN)
		printf("&& ");
	else if (comm->separator == OR)
		printf("|| ");
	else
		if (comm->pipe[OUT] == NULL)
			printf("; ");
	if (comm->next != NULL)
		disp_comm(comm->next);
	if (comm->pipe[OUT] != NULL) {
		pipe(comm->pipe[OUT]->fd);
		printf("| ");
		disp_comm(comm->pipe[OUT]->output);
	}
}

int disp_modif(comm_t **arr)
{
	printf("Did you mean : ");
	for (int i = 0; arr[i]; i++) {
		disp_comm(arr[i]);
	}
	putchar('\n');
	return (EXIT_SUCCESS);
}