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
		if ((index = test_if_exist(try, pglob, curr_path)) >= 0)
			return (pglob->gl_pathv[index]);
	}
	return (NULL);
}

char *substitute_letter(char **result, glob_t *pglob, char *curr_path)
{
	int pos = 0;
	int index = 0;
	char save = 0;

	for (int i = strlen(*result); i > 0; i--) {
		save = (*result)[pos];
		for (char letter = 'a'; letter <= 'z'; letter++) {
			(*result)[pos] = letter;
			if ((index = test_if_exist(*result, pglob, curr_path)) >= 0)
				return (pglob->gl_pathv[index]);
		}
		for (char nb = '0'; nb <= '9'; nb++) {
			(*result)[pos] = nb;
			if ((index = test_if_exist(*result, pglob, curr_path)) >= 0)
				return (pglob->gl_pathv[index]);
		}
		(*result)[pos++] = save;
	}
	return (NULL);
}