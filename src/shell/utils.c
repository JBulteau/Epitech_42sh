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
#include <stdlib.h>
#include "my.h"

int search_strtab(char **arr, char *to_find)
{
	int len = my_strlen(to_find);

	if ((arr == NULL) || (to_find == NULL))
		return (-1);
	for (int i = 0; arr[i]; i++)
		if (!my_strcmp(to_find, arr[i], len))
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