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

int correct_long(char **result, glob_t *pglob)
{
	int count_correct = 0;
	int distance_allowed = 0;

	for (int i = 0; *result[i] != '\0'; i++)
		if (i % 3 == 0)
			distance_allowed++;
	for (int i = 0; pglob->gl_pathv[i] != NULL; i++) {
		if (100 - strlen(pglob->gl_pathv[i]) / strlen(*result) < 0 || \
100 - strlen(pglob->gl_pathv[i]) / strlen(*result) > 30)
			continue;
		count_correct = count_correct_letter(distance_allowed);
	}
}

int correct_short(char **result, glob_t *pglob)
{

}