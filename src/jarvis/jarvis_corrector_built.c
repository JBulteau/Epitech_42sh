/*
** EPITECH PROJECT, 2017
** jarvis_corrector_built.c
** File description:
** built-in check
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "builtins.h"
#include <string.h>

int jarvis_corrector_built(comm_t *comm)
{
	char *both = NULL;

	for (int i = 0; builtins[i].name; i++) {
		if (strcmp(comm->argv[0], builtins[i].name) == 0)
			return (1);
	}
	if (!(comm->argv[1]))
		return (0);
	both = concat(comm->argv[0], comm->argv[1], 0, 0);
	for (int i = 0; builtins[i].name; i++) {
		if (strcmp(both, builtins[i].name) == 0) {
			free(comm->argv[0]);
			comm->argv[0] = both;
			for (int a = 1; comm->argv[a] != NULL; \
UNUSED((comm->argv[a] = comm->argv[a + 1]) && a++));
			return (2);
		}
	}
	free(both);
	return (0);
}