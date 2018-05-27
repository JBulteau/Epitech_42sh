/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo_short_no_local.c
** File description:
** no local
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <minishell.h>
#include <glob.h>

int test_if_exist_no_local(char *result, glob_t *pglob)
{
	for (int i = 0; pglob->gl_pathv[i]; i++)
		if (strcmp(result, pglob->gl_pathv[i] + \
size_before_slash(pglob->gl_pathv[i])) == 0)
			return (i);
	return (-1);
}

void switch_letters_no_local(char **result, int *index, glob_t *pglob)
{
	char save = 0;

	if (*index != -1)
		return;
	for (int a = 1; (*result)[a] && (*result)[a + 1]; a++) {
		save = (*result)[a];
		(*result)[a] = (*result)[a + 1];
		(*result)[a + 1] = save;
		*index = test_if_exist_no_local(*result, pglob);
		(*result)[a + 1] = (*result)[a];
		(*result)[a] = save;
	}
}

char *switch_adj_letter_no_local(char **result, glob_t *pglob)
{
	char save = 0;
	int index = -1;
	char *cpy = strdup(*result);

	for (int i = 0; (*result)[i] != '\0'; i++) {
		if (i != 0) {
			save = (*result)[i];
			(*result)[i] = (*result)[0];
			(*result)[0] = save;
			index = test_if_exist_no_local(*result, pglob);
		}
		switch_letters_no_local(result, &index, pglob);
		if (index != -1) {
			free(cpy);
			return (pglob->gl_pathv[index] + \
size_before_slash(pglob->gl_pathv[index]));
		}
	}
	free(*result);
	*result = cpy;
	return (NULL);
}

int correct_short_no_local(char **result, glob_t *pglob)
{
	char *c = NULL;

	if ((c = switch_adj_letter_no_local(result, pglob)) || \
(c = add_letter_no_local(result, pglob)) || \
(c = remove_letter_no_local(result, pglob)) || \
(c = substitute_letter_no_local(result, pglob))) {
		free(*result);
		(*result) = strdup(c);
		return (0);
	}
	return (42);
}