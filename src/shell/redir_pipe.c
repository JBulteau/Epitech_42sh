/*
** EPITECH PROJECT, 2017
** redir_pipe.c
** File description:
** Functions that are used for pipe redirections
*/

#include <unistd.h>
#include <stdio.h>
#include "my.h"
#include "minishell.h"

int init_redir_pipe(comm_t *comm)
{
	if (comm->pipe[IN]) {
		if (dup2(comm->pipe[IN]->fd[READ], STDIN_FILENO) == -1) {
			perror("dup2");
			return (ERROR_RETURN);
		}
	}
	if (comm->pipe[OUT]) {
		if (dup2(comm->pipe[OUT]->fd[WRITE], STDOUT_FILENO) == -1) {
			perror("dup2");
			return (ERROR_RETURN);
		}
		close(comm->pipe[OUT]->fd[READ]);
	}
	return (SUCCESS_RETURN);
}

void close_in(comm_t *curr)
{
	if (curr->pipe[IN]) {
		close(curr->pipe[IN]->fd[READ]);
		close(curr->pipe[IN]->fd[WRITE]);
	}
}