/*
** EPITECH PROJECT, 2017
** d_left.c
** File description:
** Functions for double redirection left
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "tokens.h"
#include "my.h"

void loop_d_left(comm_t *comm)
{
	char *input;

	if (isatty(STDIN_FILENO))
		my_putstr("? ");
	input = gnl(STDIN_FILENO);
	for (; input != NULL; input = gnl(STDIN_FILENO)) {
		if (!my_strcmp(input, comm->red[D_LEFT]->target, 0))
			break;
		write(comm->red[D_LEFT]->fd[0], input, strlen(input));
		write(comm->red[D_LEFT]->fd[0], "\n", 1);
		if (isatty(STDIN_FILENO))
			my_putstr("? ");
		free(input);
	}
	free(input);
}

int exec_d_left(comm_t *comm)
{
	comm->red[D_LEFT]->fd[1] = dup(STDIN_FILENO);
	comm->red[D_LEFT]->fd[0] = open("/tmp", __O_TMPFILE | O_RDWR | O_EXCL, \
S_IRWXG | S_IRWXU | S_IRWXO);
	if (comm->red[D_LEFT]->fd[0] == -1)
		return (perror("open"), -1);
	loop_d_left(comm);
	if (dup2(comm->red[D_LEFT]->fd[0], STDIN_FILENO) == -1) {
		perror("dup2");
		return (-1);
	}
	lseek(comm->red[D_LEFT]->fd[0], 0, SEEK_SET);
	return (0);
}

int end_d_left(comm_t *comm)
{
	if (dup2(comm->red[D_LEFT]->fd[1], STDIN_FILENO) == -1) {
		perror("dup2");
		return (-1);
	}
	close(comm->red[D_LEFT]->fd[0]);
	return (0);
}