/*
** EPITECH PROJECT, 2017
** cd.c
** File description:
** cd builtin fncs
*/

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "minishell.h"

int change_dir(char pwd[2][PATH_MAX], char *newdir)
{
	int exists = chdir((newdir == NULL) ? "" : newdir);

	if (exists == -1) {
		my_putstr(newdir);
		my_putstr(": ");
		my_putstr(strerror(errno));
		my_putstr(".\n");
	} else {
		my_strcpy(pwd[1], pwd[0], PATH_MAX);
		getcwd(pwd[0], PATH_MAX);
	}
	return ((exists == -1) ? 1 : 0);
}

int ptr_cd(comm_t *comm, char ***env, char pwd[2][PATH_MAX], int *retrun_code)
{
	char *home = NULL;
	int cd_res = -1;

	if (comm->argv[1] == NULL) {
		home = get_env_var(*env, "HOME=");
		if (home == NULL) {
			my_putstr("cd: No home directory.\n");
			return (1);
		}
		cd_res = change_dir(pwd, home);
		free(home);
		return (cd_res);
	} else if (!my_strcmp(comm->argv[1], "-", 0))
		return (change_dir(pwd, pwd[1]));
	else {
		if (comm->argv[2] != NULL) {
			my_putstr("cd: Too many arguments.\n");
			return (1);
		}
		return (change_dir(pwd, comm->argv[1]));
	}
}