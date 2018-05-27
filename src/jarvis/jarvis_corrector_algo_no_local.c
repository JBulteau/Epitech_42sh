/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo_no_local.c
** File description:
** function algo for no local
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <minishell.h>
#include <glob.h>

int check_lenght_no_local(glob_t *glob, char **result, int i)
{
	if ((100 - ((int)strlen(glob->gl_pathv[i] + \
size_before_slash(glob->gl_pathv[i])) * 100) / (int)strlen(*result)) < -35 || \
(100 - ((int)strlen(glob->gl_pathv[i] + size_before_slash(glob->gl_pathv[i])) \
* 100) / (int)strlen(*result)) > 35)
		return (1);
	return (0);
}

int fill_result_correct_no_local(char **result, glob_t *pglob, int i)
{
	free(*result);
	*result = strdup(pglob->gl_pathv[i] + \
size_before_slash(pglob->gl_pathv[i]));
	if (!(*result))
		return (1);
	return (0);
}

int correct_long_no_local(char **result, glob_t *glob)
{
	int count_correct = 0;
	int distance_allowed = 0;
	char *both[2] = {*result, NULL};

	for (int i = 0; (*result)[i] != '\0'; i++)
		distance_allowed += (i % 3 == 0) ? 1 : 0;
	for (int i = 0; glob->gl_pathv[i] != NULL; i++) {
		if (check_lenght_no_local(glob, result, i))
			continue;
		both[1] = glob->gl_pathv[i] + \
size_before_slash(glob->gl_pathv[i]);
		count_correct = \
count_correct_letter(distance_allowed, both);
		if (((count_correct * 100) / strlen(*result)) > 70)
			return (fill_result_correct_no_local(result, \
glob, i));
	}
	return (42);
}

int misspell_handle_comm_no_local(comm_t *comm, glob_t glob)
{
	int check = 0;

	if (strlen(comm->argv[0]) >= 4)
		check = correct_long_no_local(&(comm->argv[0]), &glob);
	else
		check = correct_short_no_local(&(comm->argv[0]), &glob);
	return ((check == 0) ? 2 : check);
}