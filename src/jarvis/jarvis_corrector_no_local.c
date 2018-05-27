/*
** EPITECH PROJECT, 2017
** jarvis_corrector_no_local.c
** File description:
** function for no local comm
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <minishell.h>
#include <glob.h>

int glob_creation(glob_t *pglob, char **path, int i)
{
	char *pattern = concat(path[i], "/*", 0, 0);
	int try = 0;

	if (!pattern) {
		free_array((void**)path);
		return (1);
	}
	if (i == 0) {
		if ((try = glob(pattern, GLOB_NOSORT, NULL, pglob)) == 2) {
			free(pattern);
			return (1);
		}
	} else {
		if ((try = glob(pattern, GLOB_APPEND, NULL, pglob)) == 2 || \
try == GLOB_NOSPACE) {
			free(pattern);
			return (1);
		}
	}
	free(pattern);
	return (0);
}

int refill_comm_spaces(char *new, comm_t *comm)
{
	free(comm->argv[0]);
	comm->argv[0] = strdup(new);
	if (!(comm->argv[0]))
		return (1);
	for (int i = 1; comm->argv[i]; i++)
		comm->argv[i] = comm->argv[i + 1];
	return (2);
}

int size_before_slash(char *str)
{
	for (int i = 0; str[i]; i++)
		if (str[i] == '/' && index_of(str + i + 1, '/') == -1)
			return (i + 1);
	return (0);
}

int spaces_handle_no_local(comm_t *comm, glob_t pglob)
{
	char *concat_comm = NULL;
	int value = 0;

	if (!(comm->argv[1]))
		return (-1);
	if ((concat_comm = concat(comm->argv[0], comm->argv[1], 0, 0)) == NULL)
		return (1);
	for (int a = 0; pglob.gl_pathv && pglob.gl_pathv[a]; a++) {
		if (strcmp(concat_comm, (pglob.gl_pathv[a] + \
size_before_slash(pglob.gl_pathv[a]))) == 0) {
			value = refill_comm_spaces((pglob.gl_pathv[a] + \
size_before_slash(pglob.gl_pathv[a])), comm);
			break;
		}
		if (!(pglob.gl_pathv[a + 1])) {
			free(concat_comm);
			return (0);
		}
	}
	free(concat_comm);
	return (value);
}

int jarvis_corrector_no_local(comm_t *comm, char ***env)
{
	int value = 0;
	char **path = NULL;
	glob_t pglob;

	if (access(comm->argv[0], X_OK) != -1)
		return (0);
	path = get_path(*env, NULL);
	if (glob_handling(path, &pglob))
		return (1);
	if (is_correct(comm, pglob))
		return (free_glob_and_path(&pglob, path));
	if ((value = spaces_handle_no_local(comm, pglob)) == 2 || value == 1) {
		free_array((void**)path);
		globfree(&pglob);
		return (value);
	}
	free_array((void**)path);
	value = misspell_handle_comm_no_local(comm, pglob);
	globfree(&pglob);
	return (value);
}