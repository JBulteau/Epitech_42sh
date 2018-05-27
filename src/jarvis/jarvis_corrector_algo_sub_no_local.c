/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo_sub_no_local.c
** File description:
** no_local
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <minishell.h>
#include <glob.h>

int loop_nb_sub_no_local(char **result, int *pos_ind, glob_t *glob)
{
	for (char nb = '0'; nb <= '9'; nb++) {
		(*result)[pos_ind[0]] = nb;
		if ((pos_ind[1] = test_if_exist_no_local(*result, glob)) >= 0)
			return (pos_ind[1]);
	}
	return (-1);
}

int loop_letter_sub_no_local(char **result, int *pos_ind, glob_t *glob)
{
	for (char letter = 'a'; letter <= 'z'; letter++) {
		(*result)[pos_ind[0]] = letter;
		if ((pos_ind[1] = test_if_exist_no_local(*result, glob)) >= 0)
			return (pos_ind[1]);
	}
	return (-1);
}

char *substitute_letter_no_local(char **result, glob_t *glob)
{
	int pos_ind[2] = {0, 0};
	char save = 0;

	for (int i = strlen(*result); i > 0; i--) {
		save = (*result)[pos_ind[0]];
		if ((pos_ind[1] = \
loop_letter_sub_no_local(result, pos_ind, glob)) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + \
size_before_slash(glob->gl_pathv[pos_ind[1]]));
		if ((pos_ind[1] = \
loop_nb_sub_no_local(result, pos_ind, glob)) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + \
size_before_slash(glob->gl_pathv[pos_ind[1]]));
		(*result)[(pos_ind[0])++] = save;
	}
	return (NULL);
}