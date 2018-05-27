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
#include <stdio.h>
#include <minishell.h>

int init_corr_command(jarg_t *corr, comm_t *comm)
{
	corr->nb_good_end = 0;
	corr->nb_good_start = 0;
	corr->change = 0;
	corr->infos = malloc(sizeof(args_t) * 2);
	if (!(corr->infos))
		return (1);
	corr->infos[1].pos = -1;
	corr->infos[0].name = strdup(comm->argv[0]);
	if (!(corr->infos[0].name))
		return (1);
	corr->infos[0].correct = 0;
	corr->infos[0].pos = 0;
	return (0);
}

int spaces_handle_comm(comm_t *comm)
{
	char *both = NULL;

	if (!(comm->argv[1]))
		return (-1);
	both = concat(comm->argv[0], comm->argv[1], 0, 0);
	if (!both)
		return (1);
	if (access(both, F_OK) == -1) {
		free(both);
		return (-1);
	}
	free(comm->argv[0]);
	comm->argv[0] = both;
	for (int i = 1; comm->argv[i] != NULL; i++)
		comm->argv[i] = comm->argv[i + 1];
	return (2);
}

int misspell_handle_comm(jarg_t *corr, comm_t *comm)
{
	char *path = NULL;
	int check = 0;

	for (int i = 0; corr->infos[i].pos != -1; i++) {
		if (check == 1)
			free(path);
		check = 0;
		if (corr->infos[i].correct == 0) {
			path = \
check_path_argv(&(comm->argv[i]), corr);
			path = \
final_check_path(path, &(comm->argv[i]), corr);
			check = 1;
		}
		if (check == 1 && path == NULL)
			return (free_ret_nb(&path, NULL, NULL, -1));
	}
	if (check == 1)
		free(path);
	return (0);
}

int jarvis_corrector_local_command(comm_t *comm)
{
	jarg_t corr;
	int value = 0;

	if (access(comm->argv[0], X_OK) != -1)
		return (0);
	if ((value = spaces_handle_comm(comm)) == 2 || value == 1)
		return (value);
	if (index_of(comm->argv[0], '/') < 0)
		return (0);
	if (init_corr_command(&corr, comm) || \
(value = misspell_handle_comm(&corr, comm)) == -1)
		return (1);
	for (value = (corr.change == 1) ? 2 : 0; value == 2; value++) {
		free(corr.infos[0].name);
		corr.infos[0].name = strdup(comm->argv[0]);
		free(comm->argv[0]);
		comm->argv[0] = concat("./", corr.infos[0].name, 0, 0);
	}
	free(corr.infos[0].name);
	free(corr.infos);
	return ((value == 3) ? --value : value);
}