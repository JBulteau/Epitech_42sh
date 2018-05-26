/*
** EPITECH PROJECT, 2017
** jarvis_corrector_local_command.c
** File description:
** function for local command
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int init_corr_command(jarg_t *corr, comm_t *comm)
{
	corr->nb_good_end = 0;
	corr->nb_good_start = 0;
	corr->change = 0;
	corr->which = NULL;
	if (comm->argv[1])
		corr->infos = malloc(sizeof(args_t) * 3);
	corr->infos[2].pos = -1;
	corr->infos[0].name = strdup(comm->argv[0]);
	corr->infos[0].correct = 0;
	corr->infos[1].name = strdup(comm->argv[1]);
	if (access(corr->infos[1].name, F_OK) != -1 || \
corr->infos[1].name[0] == '-')
		corr->infos[1].correct = 1;
	else
		corr->infos[1].correct = 0;
	return (0);
}

int jarvis_corrector_local_command(comm_t *comm, char *filepath, char ***env)
{
	jarg_t corr;

	if (access(comm->argv[0], F_OK) != -1)
		return (0);
	if (init_corr_command(&corr, comm))
		return (1);
	printf("here : %s\n%s\n", corr.infos[0].name, corr.infos[1].name);
	return (0);
}