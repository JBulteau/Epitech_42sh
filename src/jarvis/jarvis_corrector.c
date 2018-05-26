/*
** EPITECH PROJECT, 2017
** jarvis_corrector.c
** File description:
** function for jarvis corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>

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

int jarvis_corrector_arg(comm_t *comm, char *filepath, char ***env)
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
	printf("\nJarvis OP\n");
	if (corr->change == 1)
		exec(comm, filepath, *env, 1);
	free_jarvis_corrector(&corr, 0);
	return (0);
}

/* 1 = pb_command ; 2 = pb_local ; 3 = pb arg ; */

int jarvis_corrector(comm_t *comm, char ***env, int which, char *filepath)
{
	printf("hello\n");
	if (jarvis_corrector_local_command(comm, filepath, env))
		return (-1);
	if (jarvis_corrector_arg(comm, filepath, env))
		return (-1);
	return (0);
}