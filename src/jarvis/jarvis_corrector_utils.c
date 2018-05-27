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
#include <string.h>

int success_case(int *pos, char **cpy_path, int *size_check, char **arg)
{
	(*pos) += strlen(cpy_path[0]) - size_check[0];
	if (strcmp("./", cpy_path[1]) != 0)
		size_check[0] += strlen(cpy_path[1]);
	if (size_check[1] == 0) {
		if (refill_arg(arg, cpy_path[0], cpy_path[1], \
strlen((*arg) + size_check[0] + 1) + 1))
			return (1);
	} else {
		if (refill_last(arg, cpy_path[0], cpy_path[1]))
			return (1);
	}
	return (0);
}

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

int before_correct(char *cpy, char **arg, glob_t *pglob, char *concat_path_star)
{
	if (!cpy)
		return (1);
	if (access(*arg, F_OK) != -1)
		return (-1);
	if (glob(concat_path_star, GLOB_NOSORT, NULL, pglob) != 0)
		return (2);
	return (0);
}

int remove_mutliple_ending_slash(char **arg)
{
	for (int i = 0; (*arg)[i] != '\0'; i++)
		if ((*arg)[i] == '/')
			check_slash(arg, i);
	return (0);
}