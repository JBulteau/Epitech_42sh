/*
** EPITECH PROJECT, 2017
** jarvis_corrector_process.c
** File description:
** function to process our corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>

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

int misspell_handle(jarg_t *corr, comm_t *comm)
{
	return (0);
}