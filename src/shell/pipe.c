/*
** EPITECH PROJECT, 2017
** pipe.c
** File description:
** Pipe functions
*/

#include <unistd.h>
#include "minishell.h"

pipe_t *init_pipe(comm_t *in, comm_t *out)
{
	pipe_t *pipe_ = malloc(sizeof(pipe_t) * 1);

	if ((pipe_ == NULL) || (in == NULL) || (out == NULL))
		return (NULL);
	pipe_->input = in;
	in->pipe[OUT] = pipe_;
	pipe_->output = out;
	out->pipe[IN] = pipe_;
	if (pipe(pipe_->fd) == -1) {
		free(pipe_);
		return (NULL);
	}
	return (pipe_);
}

void destroy_pipe(pipe_t *pipe)
{
	close(pipe->fd[0]);
	close(pipe->fd[1]);
	free(pipe);
}