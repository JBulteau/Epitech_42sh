/*
** EPITECH PROJECT, 2017
** jarvis_corrector_algo.c
** File description:
** function to solve pb
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

int count_correct_letter(int distance_allowed, char **both)
{
	int res = 0;
	int check = 0;
	int letter_in_a_row = 0;

	for (int i = 0; both[1][i] != '\0'; i++) {
		for (int b = 0; b < i + distance_allowed; b++) {
			check = check_same(both, distance_allowed, i, b);
			letter_in_a_row = (check == 1) ? letter_in_a_row + 1 : 0;
			res += (check == 1) ? 1 : 0;
			if (letter_in_a_row == 3 && (res += 1) && \
(!(letter_in_a_row = 0))) {}
			if (check == 1)
				break;
		}
	}
	return (res);
}

int fill_result_correct(char **result, glob_t *pglob, int i, char *current_path)
{
	free(*result);
	*result = strdup(pglob->gl_pathv[i] + strlen(current_path));
	if (!(*result))
		return (1);
	return (0);
}

int correct_long(char **result, glob_t *pglob, char *curr_path)
{
	int count_correct = 0;
	int distance_allowed = 0;
	char *both[2] = {*result, NULL};

	printf("la : %s\n", curr_path);
	for (int i = 0; (*result)[i] != '\0'; i++)
		if (i % 3 == 0)
			distance_allowed++;
	for (int i = 0; pglob->gl_pathv[i] != NULL; i++) {
		if ((100 - ((int)strlen(pglob->gl_pathv[i] + strlen(curr_path)) * 100) / (int)strlen(*result)) < 0 || \
100 - (strlen(pglob->gl_pathv[i] + strlen(curr_path)) * 100) / strlen(*result) > 30)
			continue;
		both[1] = pglob->gl_pathv[i] + strlen(curr_path);
		count_correct = \
count_correct_letter(distance_allowed, both);
		if (((count_correct * 100) / strlen(*result)) > 70)
			return (fill_result_correct(result, pglob, i, curr_path));
	}
	return (1);
}

int correct_short(char **result, glob_t *pglob, char *curr_path)
{
	return (1);
}