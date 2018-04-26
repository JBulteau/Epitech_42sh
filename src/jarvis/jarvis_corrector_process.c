/*
** EPITECH PROJECT, 2017
** jarvis_corrector_process.c
** File description:
** function to process our corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>

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

int more_than_four_char(char *error, char *try)
{
	return (0);
}

char *check_path_argv(int *nb_to_path, char **arg)
{
	char *current_path = NULL;
	int pos_after_slash = 0;
	int to_know = 0;
	int letter_nbr = 0;

	for (int i = 0; (*arg)[i] != '\0'; i++)
		if ((*arg)[i] == '/' && (*arg)[i + 1] == '\0') {
			(*arg)[i] = '/0';
			to_know = 1;
		}
	for (int pos = 0; (*arg)[pos] != '\0'; pos++) {
		if (((*arg)[pos] >= '0' && (*arg)[pos] <= '9') || \
((*arg)[pos] >= 'A' && (*arg)[pos] <= 'Z') || ((*arg)[pos] >= 'a' \
&& (*arg)[pos] <= 'z'))
			letter_nbr = 1;
		if (!(pos != 0 && (*arg)[pos] == '/')) {
			//set le path a '/';
			continue;
		}
		(*arg)[pos] = '\0';
		if (letter_nbr != 1) { //fonction endessous;
			if (!(opendir(*arg))) {
				(*arg)[pos] = '/';
				return (NULL);
		} else {
			if (!(opendir(*arg))) {
				waiting;
			}
		}
		letter_nbr = 0;
		(*arg)[pos] = '/';
		ici : set current_âth + pos_after_slash;
	}

}

int misspell_handle(jarg_t *corr, comm_t *comm)
{
	char *path = NULL;
	int nb_to_path = 0;

	for (int i = 0; corr->infos[i].pos != -1; i++) {
		path = check_path_argv(&nb_to_path, &(corr->infos[i].name));
	}
	return (0);
}