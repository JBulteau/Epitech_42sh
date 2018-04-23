/*
** EPITECH PROJECT, 2017
** s_right.c
** File description:
** Functions for simple redirection right
*/

#include "minishell.h"
#include "my.h"
#include "tokens.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

char *handle_s_right(char *input, comm_t *comm)
{
	int len;

	input += my_strlen(tokens[S_RIGHT].tk);
	input = go_next_w(input, separators);
	len = get_wlen(input, separators);
	if ((comm->red[S_RIGHT]->target = my_strndup(input, len)) == NULL)
		return (NULL);
	input += len;
	return (input);
}

int exec_s_right(comm_t *comm)
{
	comm->red[S_RIGHT]->fd[0] = open(comm->red[S_RIGHT]->target, O_RDWR | O\
_CREAT | O_TRUNC, 0600);
	comm->red[S_RIGHT]->fd[1] = dup(STDOUT_FILENO);

	if (comm->red[S_RIGHT]->fd[0] == -1 || comm->red[S_RIGHT]->fd[1] == -1 \
|| dup2(comm->red[S_RIGHT]->fd[0], STDOUT_FILENO) == -1)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}


int end_s_right(comm_t *comm)
{
	close(comm->red[S_RIGHT]->fd[0]);
	if (dup2(comm->red[S_RIGHT]->fd[1], STDOUT_FILENO) == -1)
		return (ERROR_RETURN);
	close(comm->red[S_RIGHT]->fd[1]);
	return (SUCCESS_RETURN);
}