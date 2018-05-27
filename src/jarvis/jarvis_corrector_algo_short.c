/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo_short.c
** File description:
** function for short correct
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

int test_if_exist(char *result, glob_t *pglob, char *curr_path)
{
	for (int i = 0; pglob->gl_pathv[i]; i++)
		if (strcmp(result, pglob->gl_pathv[i] + strlen(curr_path)) == 0)
			return (i);
	return (-1);
}

void switch_letters(char **result, int *index, glob_t *pglob, char *curr_path)
{
	char save = 0;

	if (*index != -1)
		return;
	for (int a = 1; (*result)[a] && (*result)[a + 1]; a++) {
		save = (*result)[a];
		(*result)[a] = (*result)[a + 1];
		(*result)[a + 1] = save;
		*index = test_if_exist(*result, pglob, curr_path);
		(*result)[a + 1] = (*result)[a];
		(*result)[a] = save;
	}
}

char *switch_two_adj_letter(char **result, glob_t *pglob, char *curr_path)
{
	char save = 0;
	int index = -1;
	char *cpy = strdup(*result);

	for (int i = 0; (*result)[i] != '\0'; i++) {
		if (i != 0) {
			save = (*result)[i];
			(*result)[i] = (*result)[0];
			(*result)[0] = save;
			index = test_if_exist(*result, pglob, curr_path);
		}
		switch_letters(result, &index, pglob, curr_path);
		if (index != -1) {
			free(cpy);
			return (pglob->gl_pathv[index] + strlen(curr_path));
		}
	}
	free(*result);
	*result = cpy;
	return (NULL);
}

void prepare_try(int pos, char *result, char *try)
{
	int inc = 0;
	int len = strlen(result) + 1;

	for (int i = 0; i < len; i++) {
		if (i == pos)
			continue;
		try[i] = result[inc++];
	}
}

char *add_letter(char **result, glob_t *glob, char *curr_path)
{
	char *try = malloc(strlen(*result) + 2);
	int pos_ind[2] = {0, 0};

	try[strlen(*result) + 1] = '\0';
	for (int i = strlen(*result) + 1; i > 0; i--) {
		prepare_try((pos_ind[0])++, *result, try);
		if (loop_letter(&try, pos_ind, glob, curr_path) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + strlen(curr_path));
		if (loop_number(&try, pos_ind, glob, curr_path) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + strlen(curr_path));
	}
	free(try);
	return (NULL);
}