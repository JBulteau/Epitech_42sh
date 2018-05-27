/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo_short_add_rm_no_local.c
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

int loop_letter_no_local(char **try, int *pos_ind, glob_t *pglob)
{
	for (char letter = 'a'; letter <= 'z'; letter++) {
		(*try)[pos_ind[0] - 1] = letter;
		if ((pos_ind[1] = test_if_exist_no_local(*try, pglob)) >= 0) {
			free(*try);
			return (pos_ind[1]);
		}
	}
	return (-1);
}

int loop_number_no_local(char **try, int *pos_ind, glob_t *glob)
{
	for (char nb = '0'; nb <= '9'; nb++) {
		(*try)[pos_ind[0] - 1] = nb;
		if ((pos_ind[1] = test_if_exist_no_local(*try, glob)) >= 0) {
			free(*try);
			return (pos_ind[1]);
		}
	}
	return (-1);
}

char *add_letter_no_local(char **result, glob_t *glob)
{
	char *try = malloc(strlen(*result) + 2);
	int pos_ind[2] = {0, 0};

	try[strlen(*result) + 1] = '\0';
	for (int i = strlen(*result) + 1; i > 0; i--) {
		prepare_try((pos_ind[0])++, *result, try);
		if (loop_letter_no_local(&try, pos_ind, glob) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + \
size_before_slash(glob->gl_pathv[pos_ind[1]]));
		if (loop_number_no_local(&try, pos_ind, glob) >= 0)
			return (glob->gl_pathv[pos_ind[1]] + \
size_before_slash(glob->gl_pathv[pos_ind[1]]));
	}
	free(try);
	return (NULL);
}

char *remove_letter_no_local(char **result, glob_t *pglob)
{
	char *try = malloc(strlen(*result));
	int pos = 0;
	int index = 0;

	try[strlen(*result) - 1] = '\0';
	for (int i = strlen(*result); i > 0; i--) {
		prepare_try_rm(pos++, *result, try);
		if ((index = test_if_exist_no_local(try, pglob)) >= 0) {
			free(try);
			return (pglob->gl_pathv[index] + \
size_before_slash(pglob->gl_pathv[index]));
		}
	}
	free(try);
	return (NULL);
}