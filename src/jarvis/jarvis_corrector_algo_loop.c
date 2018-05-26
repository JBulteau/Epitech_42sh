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