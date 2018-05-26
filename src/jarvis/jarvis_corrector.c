/*
** EPITECH PROJECT, 2017
** jarvis_corrector.c
** File description:
** function for jarvis corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int free_ret_nb(char **to_free, char **to_free_2, glob_t *pglob, int nb)
{
	free(*to_free);
	if (to_free_2)
		free(*to_free_2);
	if (pglob)
		globfree(pglob);
	return (nb);
}

char *free_return_pointer(char **to_free, char *to_return)
{
	free(*to_free);
	return (to_return);
}

void put_back_last_slash(char **arg)
{
	for (int i = 0; (*arg)[i] != '\0'; i++)
		if ((*arg)[i + 1] == '\0') {
			(*arg)[i + 1] = '/';
			(*arg)[i + 2] = '\0';
			break;
		}
}

int jarvis_corrector_arg(comm_t *comm)
{
	jarg_t *corr;
	int returned_value = 1;

	if ((corr = init_struct_jarg(comm)) == NULL)
		return (-1);
	if (comm->argv[2] != NULL)
		returned_value = wrong_spaces_handle(comm, corr);
	if (returned_value == -1)
		return (-1);
	else if (returned_value == 1)
		returned_value = misspell_handle(corr, comm);
	if (returned_value == -1) {
		free_jarvis_corrector(&corr, 0);
		return (-1);
	}
	returned_value = (corr->change == 1) ? 2 : 0;
	free_jarvis_corrector(&corr, 0);
	return (returned_value);
}

int jarvis_corrector(comm_t *comm, char ***env)
{
	int ret_value = 0;
	int ret_value_arg = 0;

	if ((ret_value = jarvis_corrector_local_command(comm)) == 1)
		return (-1);
	if (comm->argv[1] != NULL && \
(ret_value_arg = jarvis_corrector_arg(comm)) < 0)
		return (-1);
	if (ret_value == 2 || ret_value_arg == 2)
		return (2);
	return (0);
}