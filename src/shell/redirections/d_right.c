/*
** EPITECH PROJECT, 2017
** d_right.c
** File description:
** Functions for double redirection right
*/

#include "minishell.h"
#include "my.h"
#include "tokens.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *handle_d_right(char *input, comm_t *comm)
{
	int len;

	input += my_strlen(tokens[D_RIGHT].tk);
	input = go_next_w(input, separators);
	len = get_wlen(input, separators);
	if ((comm->red[D_RIGHT]->target = my_strndup(input, len)) == NULL)
		return (NULL);
	input += len;
	return (input);
}

int exec_d_right(comm_t *comm)
{
	comm->red[D_RIGHT]->fd[0] = open(comm->red[D_RIGHT]->target, O_RDWR | O_CREAT | O_APPEND, 0600);
	comm->red[D_RIGHT]->fd[1] = dup(STDOUT_FILENO);

	if (comm->red[D_RIGHT]->fd[0] == -1 || comm->red[D_RIGHT]->fd[1] == -1 || dup2(comm->red[D_RIGHT]->fd[0], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

int end_d_right(comm_t *comm)
{
	close(comm->red[D_RIGHT]->fd[0]);
	dup2(comm->red[D_RIGHT]->fd[1], STDOUT_FILENO);
	close(comm->red[D_RIGHT]->fd[1]);
	return (0);
}