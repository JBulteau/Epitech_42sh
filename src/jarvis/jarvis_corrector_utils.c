/*
** EPITECH PROJECT, 2017
** jarvis_corrector_spaces_tools.c
** File description:
** tools functions for spaces handling
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void prepare_refill(jarg_t *corr, comm_t *comm, int *nb_change, int *nb_total)
{
	corr->change = 1;
	for (; corr->which[*nb_change] != -1; (*nb_change)++);
	for (; comm->argv[*nb_total] != NULL; (*nb_total)++);
	free_array((void *) comm->argv);
}

int check_lenght(glob_t *glob, char *curr_path, char **result, int i)
{
	if ((100 - ((int)strlen(glob->gl_pathv[i] + \
strlen(curr_path)) * 100) / (int)strlen(*result)) < -35 || \
(100 - ((int)strlen(glob->gl_pathv[i] + strlen(curr_path)) * 100) / \
(int)strlen(*result)) > 35)
		return (1);
	return (0);
}