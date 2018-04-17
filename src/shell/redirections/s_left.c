/*
** EPITECH PROJECT, 2017
** s_left.c
** File description:
** Functions for simple redirection left
*/

#include "minishell.h"
#include "tokens.h"
#include "my.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

char *handle_s_left(char *input, comm_t *comm)
{
	int len;

	input += my_strlen(tokens[S_LEFT].tk);
	input = go_next_w(input, separators);
	len = get_wlen(input, separators);
	if ((comm->red[S_LEFT]->target = my_strndup(input, len)) == NULL)
		return (NULL);
	input += len;
	return (input);
}

int exec_s_left(comm_t *comm)
{
	comm->red[S_LEFT]->fd[0] = open(comm->red[S_LEFT]->target, O_RDONLY);
	comm->red[S_LEFT]->fd[1] = dup(STDIN_FILENO);

	if (comm->red[S_LEFT]->fd[0] == -1)
		return (-1);
	if (comm->red[S_LEFT]->fd[1] == -1)
		return (-1);
	if (dup2(comm->red[S_LEFT]->fd[0], STDIN_FILENO) == -1)
		return (-1);
	return (0);
}


int end_s_left(comm_t *comm)
{
	close(comm->red[S_LEFT]->fd[0]);
	dup2(comm->red[S_LEFT]->fd[1], STDIN_FILENO);
	close(comm->red[S_LEFT]->fd[1]);
	return (0);
}