/*
** EPITECH PROJECT, 2017
** utils.c
** File description:
** Utils fnc
*/

#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "minishell.h"

int search_strtab(char **arr, char *to_find)
{
	int len = strlen(to_find);

	if ((arr == NULL) || (to_find == NULL))
		return (-1);
	for (int i = 0; arr[i]; i++)
		if (!strncmp(to_find, arr[i], len))
			return (i);
	return (-1);
}

int check_is_dir(char *fn)
{
	DIR *dir = opendir(fn);

	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}

char **add_arr(char **arr, char *str, int free_arr)
{
	int len = array_len((void **)arr);
	char **new_arr = malloc(sizeof(char *) * (len + 1));

	if (new_arr == NULL)
		return (NULL);
	new_arr[len] = NULL;
	new_arr[len - 1] = str;
	for (int i = 0; arr[i]; i++)
		new_arr[i] = arr[i];
	if (free_arr)
		free(arr);
	return (new_arr);
}

void clean_exit(shell_t *shell, int exit_code)
{
	free_comms(shell->comm);
	delete_shell(shell);
	exit(exit_code);
}

char **clone_arr(char **arr)
{
	int len = array_len((void *) arr);
	char **new_arr = NULL;

	if (len == -1) {
		new_arr = malloc(sizeof(char *) * 1);
		if (new_arr == NULL)
			return (NULL);
		new_arr[0] = NULL;
	} else {
		new_arr = malloc(sizeof(char *) * len);
		if (new_arr == NULL)
			return (NULL);
		for (int i = 0; arr[i]; i++)
			new_arr[i] = strdup(arr[i]);
		new_arr[len - 1] = NULL;
	}
	return (new_arr);
}