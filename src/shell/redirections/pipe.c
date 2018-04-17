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
	if ((comm->pipe = init_comm()) == NULL)
		return (NULL);
	if ((parse_command(input, comm->pipe)) == -1)
		return (NULL);
	return ("\0");
}

int exec_pipe(comm_t *comm)
{
	return (0);
}

int end_pipe(comm_t *comm)
{
	return (0);
}