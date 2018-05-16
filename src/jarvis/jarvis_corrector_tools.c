/*
** EPITECH PROJECT, 2017
** jarvis_corrector_tools.c
** File description:
** function tools for jarvis
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <my.h>
#include <string.h>

int check_same(char **both, int distance_allowed, int i, int b)
{
	int calcul_res = 0;

	if (both[0][b] == both[1][i]) {
		calcul_res = b - i;
		calcul_res *= (calcul_res < 0) ? -1 : 1;
		if (calcul_res <= distance_allowed)
			return (1);
		else
			return (0);
	}
	return (0);
}

char *prepare_copy(char **arg, char *current_path)
{
	char *res = NULL;

	if (index_of(*arg, '/') >= 0)
		res = strdup((*arg) + my_strlen(current_path));
	else
		res = strdup(*arg);
	if (!res)
		return (NULL);
}

void free_jarvis_corrector(jarg_t **corr, int i)
{
	for (int i = 0; (*corr)->infos[i].pos != -1; i++)
		free((*corr)->infos[i].name);
	free((*corr)->infos);
	if (i == 0) {
		free((*corr)->which);
		free(*corr);
	}
}

int is_slash_ending(char **arg)
{
	for (int i = 0; (*arg)[i] != '\0'; i++)
		if ((*arg)[i] == '/' && (*arg)[i + 1] == '\0') {
			(*arg)[i] = '\0';
			return (1);
		}
	return (0);
}

int is_number_or_letter(char **arg, int pos)
{
	if (((*arg)[pos] >= '0' && (*arg)[pos] <= '9') || \
((*arg)[pos] >= 'A' && (*arg)[pos] <= 'Z') || ((*arg)[pos] >= 'a' \
&& (*arg)[pos] <= 'z'))
		return (1);
	return (0);
}