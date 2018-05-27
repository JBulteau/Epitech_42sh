/*
** EPITECH PROJECT, 2017
** which_where.c
** File description:
** Which and where builtins
*/

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"
#include "my.h"

int check_folder(char* path)
{
	DIR* directory = opendir(path);

	if (directory != NULL) {
		closedir(directory);
		return (1);
	} else
		return (0);
	return (-1);
}

char *search_folder(char *folder, char *name)
{
	char *fn = NULL;
	int rights[2] = {0, 0};

	if ((fn = concat(folder, concat("/", name, 0, 0), 0, 1)) == NULL)
		return (NULL);
	rights[0] = access(fn, F_OK);
	rights[1] = access(fn, X_OK);
	if (rights[0] == 0 && rights[1] == 0)
		return (fn);
	free(fn);
	return (NULL);
}

int ptr_where(comm_t *comm, shell_t *shell)
{
	char **path = NULL;
	char *filepath;
	int status = 0;
	int err = 0;

	if (comm->argv[1] == NULL) {
		fprintf(stderr, "where: Too few arguments.\n");
		return (EXIT_FAILURE);
	}
	for (int i = 1; comm->argv[i]; UNUSED(i++ && (status = 0))) {
		if (is_builtin(comm->argv[i]) != -1)
			printf("%s: shell built-in command.\n", comm->argv[i]);
		else if (index_of(comm->argv[i], '/') != ERROR_RETURN) {
			printf("where: / in command makes no sense\n");
		} else {
			path = get_path(shell->env, shell->vars);
			for (int j = 0; path && path[j]; j++) {
				filepath = search_folder(path[j], comm->argv[i]);
				if (filepath != NULL) {
					printf("%s\n", filepath);
					free(filepath);
				} else
					status++;
			}
			if (status)
				err = 1;
		}
	}
	free_array((void **)path);
	return (err);
}

int ptr_which(comm_t *comm, shell_t *shell)
{
	int status = 0;
	char **path = get_path(shell->env, shell->vars);
	char *filepath = NULL;

	if (comm->argv[1] == NULL) {
		fprintf(stderr, "which: Too few arguments.\n");
		return (EXIT_FAILURE);
	}
	for (int i = 1; comm->argv[i]; i++) {
		if (is_builtin(comm->argv[i]) != -1)
			printf("%s: shell built-in command.\n", comm->argv[i]);
		else if (index_of(comm->argv[i], '/') != ERROR_RETURN) {
			if (access(comm->argv[i], X_OK) == -1 || check_folder(comm->argv[i]) != 0)
				status = 1;
			else
				printf("%s\n", comm->argv[i]);
		} else {
			filepath = search_path(path, comm->argv[i]);
			if (filepath == NULL) {
				status = 1;
			} else {
				printf("%s\n", filepath);
				free(filepath);
			}
		}
	}
	free_array((void **)path);
	return (status);
}