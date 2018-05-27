/*
** EPITECH PROJECT, 2017
** which_where.c
** File description:
** Which and where builtins
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"
#include "my.h"

int sub_loop(char *path, char *arg)
{
	char *filepath = search_folder(path, arg);
	if (filepath != NULL) {
		if (!strncmp(filepath, "/usr/bin", 8))
			printf("/bin/%s\n", arg);
		printf("%s\n", filepath);
		free(filepath);
	} else
		return (1);
	return (0);
}

int where_loop(comm_t *comm, int i, shell_t *shell)
{
	char **path = NULL;
	int status = 0;

	if (is_builtin(comm->argv[i]) != -1)
		printf("%s: shell built-in command.\n", comm->argv[i]);
	else if (index_of(comm->argv[i], '/') != ERROR_RETURN) {
		printf("where: / in command makes no sense\n");
	} else {
		path = get_path(shell->env, shell->vars);
		for (int j = 0; path && path[j]; j++) {
			status += sub_loop(path[j], comm->argv[i]);
		}
		free_array((void **)path);
	}
	return (status);
}

int ptr_where(comm_t *comm, shell_t *shell)
{
	int err = 0;

	if (comm->argv[1] == NULL) {
		fprintf(stderr, "where: Too few arguments.\n");
		return (EXIT_FAILURE);
	}
	for (int i = 1; comm->argv[i]; i++) {
		if (where_loop(comm, i, shell) != 0)
			err = 1;
	}
	return (err);
}

void wich_loop(comm_t *comm, int *status, char **path, int i)
{
	char *filepath = NULL;

	if (is_builtin(comm->argv[i]) != -1)
		printf("%s: shell built-in command.\n", comm->argv[i]);
	else if (index_of(comm->argv[i], '/') != ERROR_RETURN) {
		if (access(comm->argv[i], X_OK) == -1 || check_folder\
(comm->argv[i]) != 0)
			(*status) = 1;
		else
			printf("%s\n", comm->argv[i]);
	} else {
		filepath = search_path(path, comm->argv[i]);
		if (filepath == NULL) {
			(*status) = 1;
		} else {
			printf("%s\n", filepath);
			free(filepath);
		}
	}
}

int ptr_which(comm_t *comm, shell_t *shell)
{
	int status = 0;
	char **path = get_path(shell->env, shell->vars);

	if (comm->argv[1] == NULL) {
		fprintf(stderr, "which: Too few arguments.\n");
		return (EXIT_FAILURE);
	}
	for (int i = 1; comm->argv[i]; i++)
		wich_loop(comm, &status, path, i);
	free_array((void **)path);
	return (status);
}