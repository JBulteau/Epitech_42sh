/*
** EPITECH PROJECT, 2017
** cd.c
** File description:
** cd builtin fncs
*/

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

int change_dir(char pwd[2][PATH_MAX], char *newdir)
{
	int exists = chdir((newdir == NULL) ? "" : newdir);

	if (exists == -1) {
		fprintf(stderr, "%s: %s.\n", newdir, strerror(errno));
	} else {
		strncpy(pwd[1], pwd[0], PATH_MAX);
		getcwd(pwd[0], PATH_MAX);
	}
	return ((exists == -1) ? 1 : 0);
}

int ptr_cd(comm_t *comm, shell_t *shell)
{
	char *home = NULL;
	int cd_res = -1;

	if (comm->argv[1] == NULL) {
		if ((home = get_var(NULL, shell->vars, "home")) == NULL)
			home = get_var(shell->env, NULL, "HOME");
		if (home == NULL)
			return (puts("cd: No home directory.") != -1);
		cd_res = change_dir(shell->pwd, home);
		free(home);
		return (cd_res);
	} else if (!strcmp(comm->argv[1], "-"))
		return (change_dir(shell->pwd, shell->pwd[1]));
	else {
		if (comm->argv[2] != NULL) {
			puts("cd: Too many arguments.");
			return (1);
		}
		return (change_dir(shell->pwd, comm->argv[1]));
	}
}
