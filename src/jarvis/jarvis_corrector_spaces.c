/*
** EPITECH PROJECT, 2017
** jarvis_corrector_process.c
** File description:
** function to process our corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int try_concat(comm_t *comm, jarg_t *corr, int *which_inc, int *i)
{
	char *both = concat(corr->infos[*i].name, \
corr->infos[*i + 1].name, 0, 0);

	if (access(both, F_OK) == 0) {
		corr->nb_good_end += 1;
		corr->which[*which_inc] = corr->infos[*i].pos;
		(*which_inc)++;
		(*i)++;
	}
	free(both);
	return (1);
}

int wrong_spaces_handle(comm_t *comm, jarg_t *corr)
{
	int which_inc = 0;
	int check = 1;

	for (int i = 0; corr->infos[i].pos != -1 && corr->infos[i + 1].pos != -1; i++) {
		if (corr->infos[i].correct == 0 && \
corr->infos[i + 1].correct == 0 && (try_concat(comm, corr, &which_inc, &i)))
			continue;
		else if (corr->infos[i].correct == 0 && \
corr->infos[i + 1].correct == 0)
			break;
	}
	if (corr->nb_good_start < corr->nb_good_end)
		if ((check = refill_comm_struct(comm, corr)) == -1)
			return (-1);
	return (check);
}

int fill_comm(comm_t *comm, jarg_t *corr, int *inc)
{
	if (inc[INFOS_INC] + 1 == corr->which[inc[WHICH_INC]]) {
		comm->argv[inc[COMM_INC]] = concat(corr->infos[inc[INFOS_INC]].\
name, corr->infos[inc[INFOS_INC] + 1].name, 0, 0);
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

int refill_infos(comm_t *comm, jarg_t *corr)
{
	int nb_argv = 0;

	corr->nb_good_start = 0;
	for (int i = 1; comm->argv[i] != NULL; i++ && nb_argv++);
	corr->infos = malloc(sizeof(args_t) * (nb_argv + 1));
	if (corr->infos == NULL)
		return (-1);
	corr->infos[nb_argv].pos = -1;
	for (int i = 1; comm->argv[i] != NULL; i++)
		fill_infos(comm, corr, i, &nb_argv);
	return (0);
}

int refill_comm_struct(comm_t *comm, jarg_t *corr)
{
	int inc[3] = {0, 0, 1};
	int nb_change = 0;
	int nb_total = 0;
	char *save = my_strndup(comm->argv[0], my_strlen(comm->argv[0]));

	prepare_refill(corr, comm, &nb_change, &nb_total);
	comm->argv = malloc(sizeof(char*) * (nb_total - nb_change + 1));
	if (comm->argv == NULL)
		return (-1);
	comm->argv[nb_total - nb_change] = NULL;
	comm->argv[0] = save;
	for (; corr->infos[inc[INFOS_INC]].pos != -1; (inc[INFOS_INC])++)
		if (fill_comm(comm, corr, inc) == 1)
			continue;
	free_jarvis_corrector(&corr, 1);
	if (refill_infos(comm, corr) == -1)
		return (-1);
	for (int i = 0; corr->infos[i].pos != -1; i++)
		if (corr->infos[i].correct == 0)
			return (1);
	return (0);
}
