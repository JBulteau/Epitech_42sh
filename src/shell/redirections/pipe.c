/*
** EPITECH PROJECT, 2017
** pipe.c
** File description:
** Functions that handle pipes
*/

#include "minishell.h"
#include "my.h"

char *handle_pipe(char *input, comm_t *comm)
{
	input = go_next_w(input + 1, separators);
	if ((comm->pipe[OUT] = init_pipe(comm, init_comm())) == NULL)
		return (NULL);
	comm->pipe[OUT]->input = comm;
	comm->pipe[OUT]->output->pipe[IN] = comm->pipe[OUT];
	if ((parse_command(input, comm->pipe[OUT]->output)) == -1)
		return (NULL);
	return ("\0");
}
