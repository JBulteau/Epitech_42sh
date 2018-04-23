/*
** EPITECH PROJECT, 2017
** d_left.c
** File description:
** Functions for double redirection left
*/

#include "minishell.h"
#include "tokens.h"
#include "my.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

char *handle_d_left(char *input, comm_t *comm)
{
	int len;

	input += my_strlen(tokens[D_LEFT].tk);
	input = go_next_w(input, separators);
	len = get_wlen(input, separators);
	if ((comm->red[D_LEFT]->target = my_strndup(input, len)) == NULL)
		return (NULL);
	input += len;
	return (input);
}

int exec_d_left(comm_t *comm)
{
	char *input = gnl(STDIN_FILENO);

	for (; input != NULL; input = gnl(STDIN_FILENO)) {
		if (!my_strcmp(input, comm->red[D_LEFT]->target, 0)) {
			puts("BREAK");
			puts(input);
			break;
		}
		puts(input);
		if (isatty(STDIN_FILENO))
			my_putstr("? ");
		free(input);
	}
	free(input);
	return (SUCCESS_RETURN);
}

int end_d_left(comm_t *comm)
{
	return (0);
}