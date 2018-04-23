/*
** EPITECH PROJECT, 2017
** jarvis_corrector_process.c
** File description:
** function to process our corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>

void try_concat(comm_t *comm, jarg_t *corr, int *which_inc, int *i)
{
	char *both = concat(corr->infos[*i].name, \
corr->infos[*i + 1].name, 0, 0);
	DIR *dirp;

	if (dirp = opendir(both)) {
		corr->nb_good_end += 1;
		corr->which[*which_inc] = corr->infos[*i].pos;
		(*which_inc)++;
		(*i)++;
		closedir(dirp);
	}
}

int wrong_spaces_handle(comm_t *comm, jarg_t *corr)
{
	int which_inc = 0;

	for (int i = 0; corr->infos[i + 1].pos != -1; i++) {
		if (corr->infos[i].correct == 0 && \
corr->infos[i + 1].correct == 0) {
			try_concat(comm, corr, &which_inc, &i);
			if (corr->infos[i + 1].pos != -1)
				continue;
			else
				break;
		}
	}
	if (corr->nb_good_start < corr->nb_good_end)
		if ((which_inc = refill_comm_struct(comm, corr)) == -1)
			return (-1);
	if (which_inc == 0)
		return (0);
	else
		return (1);
}

int fill_comm(comm_t *comm, jarg_t *corr, int *inc)
{
	if (inc[INFOS_INC] + 1 == corr->which[inc[WHICH_INC]]) {
		comm->argv[inc[COMM_INC]] = \
my_strndup(concat(corr->infos[inc[INFOS_INC]].name, corr->infos[inc[INFOS_INC] \
+ 1].name, 0, 0), 0);
		(inc[INFOS_INC])++;
		(inc[COMM_INC])++;
		(inc[WHICH_INC])++;
		return (1);
	} else {
		comm->argv[inc[COMM_INC]] = \
my_strndup(corr->infos[inc[INFOS_INC]].name, 0);
		(inc[COMM_INC])++;
	}
	return (0);
}

int refill_comm_struct(comm_t *comm, jarg_t *corr)
{
	int inc[3] = {0, 0, 1};
	int nb_change = 0;
	int nb_total = 0;
	char *save = my_strndup(comm->argv[0], my_strlen(comm->argv[0]));

	for (; corr->which[nb_change] != -1; nb_change++);
	for (; comm->argv[nb_total] != NULL; nb_total++);
	free_array((void *) comm->argv);
	comm->argv = malloc(sizeof(char*) * (nb_total - nb_change + 1));
	if (comm->argv == NULL)
		return (-1);
	comm->argv[nb_total - nb_change] = NULL;
	comm->argv[0] = save;
	for (; corr->infos[inc[INFOS_INC]].pos != -1; (inc[INFOS_INC])++)
		if (fill_comm(comm, corr, inc) == 1)
			continue;
	return (0);
}
