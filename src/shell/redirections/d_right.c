/*
** EPITECH PROJECT, 2017
** d_right.c
** File description:
** Functions for double redirection right
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "tokens.h"
#include "my.h"

int exec_d_right(comm_t *comm)
{
	comm->red[D_RIGHT]->fd[0] = open(comm->red[D_RIGHT]->target, O_RDWR | O\
_CREAT | O_APPEND, 0600);
	comm->red[D_RIGHT]->fd[1] = dup(STDOUT_FILENO);

	if (comm->red[D_RIGHT]->fd[0] == -1 || comm->red[D_RIGHT]->fd[1] == -1 \
|| dup2(comm->red[D_RIGHT]->fd[0], STDOUT_FILENO) == -1)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int end_d_right(comm_t *comm)
{
	close(comm->red[D_RIGHT]->fd[0]);
	if (dup2(comm->red[D_RIGHT]->fd[1], STDOUT_FILENO) == -1)
		return (ERROR_RETURN);
	close(comm->red[D_RIGHT]->fd[1]);
	return (SUCCESS_RETURN);
}