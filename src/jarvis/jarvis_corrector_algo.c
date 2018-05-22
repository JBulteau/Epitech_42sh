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

/*static const char *commands[] = {
	"line",
};*/

int count_correct_letter(int dist_allow, char **both)
{
	int res = 0;
	int check = 0;
	int letter_in_row = 0;

	for (int i = 0; both[1][i] != '\0'; i++) {
		check = 0;
		for (int b = 0; (b < i + dist_allow && both[0][b] != '\0') && \
check != 1; b++) {
			check = check_same(both, dist_allow, i, b);
			letter_in_row = (check == 1) ? letter_in_row + 1 : 0;
			res += (check == 1) ? 1 : 0;
			if (letter_in_row == 3 && (res += 1) && \
(!(letter_in_row = 0))) {}
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

int correct_short(char **result, glob_t *pglob, char *curr_path)
{
	char *c = NULL;

	if ((c = switch_two_adj_letter(result, pglob, curr_path)) || \
(c = add_letter(result, pglob, curr_path)) /*|| other way */) {
		free(*result);
		(*result) = strdup(c);
		return (0);
	}
	return (1);
}

int correct_long(char **result, glob_t *glob, char *curr_path)
{
	int count_correct = 0;
	int distance_allowed = 0;
	char *both[2] = {*result, NULL};

	for (int i = 0; (*result)[i] != '\0'; i++)
		distance_allowed += (i % 3 == 0) ? 1 : 0;
	for (int i = 0; glob->gl_pathv[i] != NULL; i++) {
		if (check_lenght(glob, curr_path, result, i))
			continue;
		both[1] = glob->gl_pathv[i] + strlen(curr_path);
		count_correct = \
count_correct_letter(distance_allowed, both);
		if (((count_correct * 100) / strlen(*result)) > 70)
			return (fill_result_correct(result, \
glob, i, curr_path));
	}
	return (42);
}

int put_back_ending_slash(int pos, char **arg, int to_know)
{
	if ((*arg)[pos + 1] == '\0' && to_know == 1) {
		(*arg)[pos + 1] = '/';
		(*arg)[pos + 2] = '\0';
		return (1);
	}
	return (0);
}