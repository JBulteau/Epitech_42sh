/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo_loop.c
** File description:
** function loop
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

int glob_handling(char **path, glob_t *glob)
{
	for (int i = 0; path[i]; i++)
		if (glob_creation(glob, path, i)) {
			free_array((void**)path);
			return (1);
		}
	return (0);
}

int loop_letter(char **try, int *pos_ind, glob_t *pglob, char *curr_path)
{
	for (char letter = 'a'; letter <= 'z'; letter++) {
		(*try)[pos_ind[0] - 1] = letter;
		if ((pos_ind[1] = test_if_exist(*try, pglob, curr_path)) >= 0) {
			free(*try);
			return (pos_ind[1]);
		}
	}
	return (-1);
}

int loop_number(char **try, int *pos_ind, glob_t *glob, char *curr_path)
{
	for (char nb = '0'; nb <= '9'; nb++) {
		(*try)[pos_ind[0] - 1] = nb;
		if ((pos_ind[1] = test_if_exist(*try, glob, curr_path)) >= 0) {
			free(*try);
			return (pos_ind[1]);
		}
	}
	return (-1);
}

int is_correct(comm_t *comm, glob_t glob)
{
	int size = 0;

	for (int i = 0; glob.gl_pathv && glob.gl_pathv[i]; i++) {
		size = size_before_slash(glob.gl_pathv[i]);
		if (strcmp(glob.gl_pathv[i] + size, comm->argv[0]) == 0)
			return (1);
	}
	return (0);
}

int free_glob_and_path(glob_t *glob, char **path)
{
	globfree(glob);
	free_array((void**)path);
	return (0);
}