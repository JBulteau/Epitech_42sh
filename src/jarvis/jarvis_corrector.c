/*
** EPITECH PROJECT, 2017
** jarvis_corrector.c
** File description:
** function for jarvis corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>

static int last_part_init(jarg_t *corr, comm_t *comm, int *nb_argv, int *i)
{
	if (corr->infos[*i].correct == 0 && \
corr->infos[*i + 1].correct == 0) {
		(*nb_argv)++;
		(*i)++;
		if (corr->infos[*i + 1].pos != -1)
			return (1);
		else
			return (2);
	}
	return (0);
}

static int first_part_init(jarg_t *corr, comm_t *comm, int *nb_argv)
{
	if (corr == NULL)
		return (-1);
	corr->nb_good_start = 0;
	for (int i = 1; comm->argv[i] != NULL; i++ && (*nb_argv)++);
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
		corr->infos[i - 1].correct = 1;
		corr->infos[i - 1].name = my_strndup("options", 7);
	} else if (opendir(comm->argv[i])) {
		corr->nb_good_start += 1;
		corr->infos[i - 1].name = my_strndup(comm->argv[i], \
my_strlen(comm->argv[i]));
		corr->infos[i - 1].correct = 1;
		corr->infos[i - 1].pos = i;
	} else {
		corr->infos[i - 1].name = my_strndup(comm->argv[i], \
my_strlen(comm->argv[i]));
		corr->infos[i - 1].correct = 0;
		corr->infos[i - 1].pos = i;
	}
	*nb_argv = 0;
}

jarg_t *init_struct_jarg(comm_t *comm)
{
	jarg_t *corr = malloc(sizeof(jarg_t) * 1);
	int nb_argv = 0;
	int check = 0;

	if (first_part_init(corr, comm, &nb_argv) == -1)
		return (NULL);
	for (int i = 1; comm->argv[i] != NULL; i++)
		fill_infos(comm, corr, i, &nb_argv);
	for (int i = 0; corr->infos[i].pos != -1; i++);
	corr->which = NULL;
	for (int i = 0; corr->infos[i + 1].pos != -1; i++)
		if ((check = last_part_init(corr, comm, &nb_argv, &i)) == 1)
			continue;
		else if (check == 2)
			break;
	if (nb_argv > 0 && (corr->which = malloc(sizeof(int) * \
(nb_argv + 1))) == NULL)
		return (NULL);
	for (int i = 0; nb_argv > 0 && i <= nb_argv; corr->which[i++] = -1);
	corr->nb_good_end = corr->nb_good_start;
	return (corr);
}

int jarvis_corrector(comm_t *comm, char ***env, int which, char *filepath)
{
	int returned_value = 1;
	jarg_t *corr = NULL;

	if (which == 1) { //pb_command

	} else if (which == 2) { //pb_local

	} else { //pb_arg
		if ((corr = init_struct_jarg(comm)) == NULL)
			return (-1);
		if (comm->argv[2] != NULL)
			returned_value = wrong_spaces_handle(comm, corr);
		if (returned_value == -1)
			return (-1);
		else if (returned_value == 1)
			returned_value = misspell_handle(corr, comm);
		if (returned_value == -1)
			return (-1);
		printf("Jarvis OP\n");
		if (corr->nb_good_start < corr->nb_good_end)
			exec(comm, filepath, *env, 1);
	}
	return (0);
}