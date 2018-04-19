/*
** EPITECH PROJECT, 2017
** commands.c
** File description:
** Functions that manages commands
*/

#include "tokens.h"
#include "minishell.h"
#include "my.h"

void free_comm(comm_t *comm)
{
	if (comm->pipe[OUT]) {
		free_comm(comm->pipe[OUT]->output);
		free(comm->pipe[OUT]);
	}
	free_array((void **) comm->argv);
	free_red(comm->red[S_RIGHT]);
	free_red(comm->red[S_LEFT]);
	free_red(comm->red[D_LEFT]);
	free_red(comm->red[D_RIGHT]);
	free(comm);
	return;
}

int exec_start(comm_t *comm)
{
	for (int i = 0; i < 4; i++) {
		if (comm->red[i]) {
			tokens[i].fnc_exec(comm);
		}
	}
}

int exec_end(comm_t *comm)
{
	for (int i = 0; i < 4; i++)
		if (comm->red[i])
			tokens[i].end_exec(comm);
}

comm_t *init_comm(void)
{
	comm_t *comm = malloc(sizeof(comm_t) * 1);

	if (comm == NULL)
		return (NULL);
	for (int j = 0; j <= S_LEFT; j++)
		comm->red[j] = NULL;
	if ((comm->argv = malloc(sizeof(char **) * 1)) == NULL)
		return (NULL);
	comm->argv[0] = NULL;
	comm->pipe[OUT] = NULL;
	comm->pipe[IN] = NULL;
	return (comm);
}

void free_comms(comm_t **comm)
{
	for (int i = 0; comm[i]; i++) {
		free_comm(comm[i]);
	}
	free(comm);
}