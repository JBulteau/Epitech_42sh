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

	for (int i = 0; (*result)[i] != '\0'; i++) {
		if (i != 0) {
			save = (*result)[i];
			(*result)[i] = (*result)[0];
			(*result)[0] = save;
			index = test_if_exist(*result, pglob, curr_path);
		}
		if (index != -1)
			return (pglob->gl_pathv[index]);
		switch_letters(result, &index, pglob, curr_path);
		if (index != -1)
			return (pglob->gl_pathv[index]);
	}
	return (NULL);
}

char *add_letter(char **result, glob_t *pglob, char *curr_path)
{
	
}