/*
** EPITECH PROJECT, 2017
** redir.c
** File description:
** Redir fnc
*/

#include "minishell.h"

void free_red(redir_t *red)
{
	if (!red)
		return;
	free(red->target);
	free(red);
}

redir_t *init_redir(void)
{
	redir_t *red = malloc(sizeof(redir_t) * 1);

	if (red == NULL)
		return (NULL);
	red->fd[0] = -2;
	red->fd[1] = -2;
	red->target = NULL;
	return (red);
}