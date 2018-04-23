/*
** EPITECH PROJECT, 2017
** jarvis_corrector.c
** File description:
** function for jarvis corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>

int more_than_two_argv_handling(comm_t *comm, char *filepath, char **env)
{
	char *argv_fusion = concat(comm->argv[1], comm->argv[2], 0, 0);

	if (opendir(argv_fusion)) {
		free(comm->argv[2]);
		free(comm->argv[1]);
		comm->argv[1] = argv_fusion;
		comm->argv[2] = NULL;
		return (exec(comm, filepath, env, 1));
	}
}

// if which : 1 pb command | 2 pb local | 3 pb arg

int jarvis_corrector(comm_t *comm, char ***env, int which, char *filepath)
{
	if (which == 1) { //pb_command

	} else if (which == 2) { //pb_local

	} else { //pb_arg
		if (comm->argv[2] != NULL)
			function1; // return 1 si encore certains sont faux, 0 si all good
		if (function1 returned 1 || !opendir(comm->argv[2]))
			function2;
		else
			function3;

	}
	return (0);
}