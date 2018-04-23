/*
** EPITECH PROJECT, 2017
** jarvis_corrector.c
** File description:
** function for jarvis corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>

// if which : 1 pb command | 2 pb local | 3 pb arg
//return -1 == probleme appel systeme

static int first_part_init(jarg_t *corr, comm_t *comm, int *nb_argv)
{
	if (corr == NULL)
		return (-1);
	corr->nb_good_start = 0;
	corr->nb_good_end = 0;
	for (; comm->argv[*nb_argv] != NULL; (*nb_argv)++);
	corr->infos = malloc(sizeof(args_t) * (*nb_argv + 1));
	if (corr->infos == NULL)
		return (-1);
	corr->infos[*nb_argv].pos = -1;
	return (0);
}

static void fill_infos(comm_t *comm, jarg_t *corr, int i, int *nb_argv)
{
	if (comm->argv[i][0] == '-') {
		corr->infos[i - 1].pos = -2;
		corr->infos[i - 1].correct == 1;
		corr->infos[i - 1].name = my_strndup("options", 7);
	} else if (opendir(comm->argv[i])) {
		corr->nb_good_start += 1;
		corr->infos[i - 1].name = my_strndup(comm->argv[i], \
my_strlen(comm->argv[i]));
		corr->infos[i - 1].correct == 1;
		corr->infos[i - 1].pos = i;
	} else {
		corr->infos[i - 1].name = my_strndup(comm->argv[i], \
my_strlen(comm->argv[i]));
		corr->infos[i - 1].correct == 0;
		corr->infos[i - 1].pos = i;
	}
	*nb_argv = 0;
}

jarg_t *init_struct_jarg(comm_t *comm)
{
	jarg_t *corr = malloc(sizeof(jarg_t) * 1);
	int nb_argv = 0;

	if (first_part_init(corr, comm, &nb_argv) == -1)
		return (NULL);
	for (int i = 1; comm->argv[i] != NULL; i++)
		fill_infos(comm, corr, i, &nb_argv);
	corr->which = NULL;
	for (int i = 0; corr->infos[i + 1].pos != -1; i++)
		if (corr->infos[i].correct == 0 && \
corr->infos[i + 1].correct == 0) {
			nb_argv++;
			i++;
		}
	if ((corr->which = malloc(sizeof(int) * (nb_argv + 1))) == NULL)
		return (NULL);
	for (int i = 0; i < nb_argv; i++)
		corr->which[i] = 0;
	return (corr);
}

int jarvis_corrector(comm_t *comm, char ***env, int which, char *filepath)
{
	int returned_value = 0;
	jarg_t *corr = NULL;

	if (which == 1) { //pb_command

	} else if (which == 2) { //pb_local

	} else { //pb_arg
		if ((corr = init_struct_jarg(comm)) == NULL)
			return (-1);
		//if (comm->argv[2] != NULL)
			//returned_value = wrong_spaces_handle(comm, corr); // return 1 si encore certains sont faux, 0 si all good
		//if (returned_value == 1 || !opendir(comm->argv[2]))
			//function2;
	}
	return (0);
}