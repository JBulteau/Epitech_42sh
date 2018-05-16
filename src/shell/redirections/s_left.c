/*
** EPITECH PROJECT, 2017
** s_left.c
** File description:
** Functions for simple redirection left
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "my.h"
#include "minishell.h"
#include "tokens.h"

char *handle_s_left(char *input, comm_t *comm)
{
	int len;

	input += strlen(tokens[S_LEFT].tk);
	input = go_next_w(input, separators);
	len = get_wlen(input, separators);
	if ((comm->red[S_LEFT]->target = strndup(input, len)) == NULL)
		return (NULL);
	input += len;
	return (input);
}

int exec_s_left(comm_t *comm)
{
	comm->red[S_LEFT]->fd[0] = open(comm->red[S_LEFT]->target, O_RDONLY);
	comm->red[S_LEFT]->fd[1] = dup(STDIN_FILENO);

	if ((comm->red[S_LEFT]->fd[0] == -1) || (comm->red[S_LEFT]->fd[1] == -1\
) || (dup2(comm->red[S_LEFT]->fd[0], STDIN_FILENO) == -1))
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int end_s_left(comm_t *comm)
{
	close(comm->red[S_LEFT]->fd[0]);
	if (dup2(comm->red[S_LEFT]->fd[1], STDIN_FILENO) == -1)
		return (ERROR_RETURN);
	close(comm->red[S_LEFT]->fd[1]);
	return (SUCCESS_RETURN);
}