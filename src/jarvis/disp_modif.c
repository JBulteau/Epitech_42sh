/*
** EPITECH PROJECT, 2017
** disp_modif.c
** File description:
** Display did you mean
*/

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"

int disp_comm(comm_t *comm)
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
		if (pipe(comm->pipe[OUT]->fd) == ERROR_RETURN)
			return (ERROR_RETURN);
		printf("| ");
		disp_comm(comm->pipe[OUT]->output);
	}
	return (SUCCESS_RETURN);
}

int disp_modif(comm_t **arr)
{
	printf("Did you mean : ");
	for (int i = 0; arr[i]; i++) {
		if (disp_comm(arr[i]) == ERROR_RETURN) {
			fprintf(stderr, "An error has ccured\n");
			return (0);
		}
	}
	putchar('\n');
	return (1);
}