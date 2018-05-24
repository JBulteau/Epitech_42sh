/*
** EPITECH PROJECT, 2017
** jarvis_corrector_short_rm_sub.c
** File description:
** function for rm letters and substitutes
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

void prepare_try_rm(int pos, char *result, char *try)
{
	int inc = 0;
	int len = strlen(result);

	for (int i = 0; i < len; i++) {
		if (i == pos)
			continue;
		try[inc++] = result[i];
	}
}

char *remove_letter(char **result, glob_t *pglob, char *curr_path)
{
	char *try = malloc(strlen(*result));
	int pos = 0;
	int index = 0;

	try[strlen(*result) - 1] = '\0';
	for (int i = strlen(*result); i > 0; i--) {
		prepare_try_rm(pos++, *result, try);
		if ((index = test_if_exist(try, pglob, curr_path)) >= 0) {
			free(try);
			return (pglob->gl_pathv[index] + strlen(curr_path));
		}
	}
	free(try);
	return (NULL);
}

int loop_letter_sub(char **result, int *pos_ind, glob_t *glob, char *curr_path)
{
	for (char letter = 'a'; letter <= 'z'; letter++) {
		(*result)[pos_ind[0]] = letter;
		if ((pos_ind[1] = test_if_exist(*result, glob, curr_path)) >= 0)
			return (pos_ind[1]);
	}
	return (-1);
}

int loop_nb_sub(char **result, int *pos_ind, glob_t *glob, char *curr_path)
{
	for (char nb = '0'; nb <= '9'; nb++) {
		(*result)[pos_ind[0]] = nb;
		if ((pos_ind[1] = test_if_exist(*result, glob, curr_path)) >= 0)
			return (pos_ind[1]);
	}
	return (-1);
}

char *substitute_letter(char **result, glob_t *glob, char *curr_path)
{
	int pos_ind[2] = {0, 0};
	char save = 0;

	for (int i = strlen(*result); i > 0; i--) {
		save = (*result)[pos_ind[0]];
		if ((pos_ind[1] = \
loop_letter_sub(result, pos_ind, glob, curr_path)) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + strlen(curr_path));
		if ((pos_ind[1] = \
loop_nb_sub(result, pos_ind, glob, curr_path)) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + strlen(curr_path));
		(*result)[(pos_ind[0])++] = save;
	}
	return (NULL);
}