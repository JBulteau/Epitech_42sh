/*
** EPITECH PROJECT, 2017
** source.c
** File description:
** Source builtin
*/

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"

int ptr_source(comm_t *comm, shell_t *shell)
{
	if (comm->argv[1] == NULL)
		return (fprintf(stderr, "Too few arguments.\n") != -1);
	for (int i = 1; comm->argv[i]; i++) {
		if (access(comm->argv[i], R_OK) == -1) {
			perror(comm->argv[i]);
			continue;
		}
		if (source_that_file(shell, comm->argv[i]) == ERROR_RETURN)
			return (EXIT_FAILURE);
	}
}