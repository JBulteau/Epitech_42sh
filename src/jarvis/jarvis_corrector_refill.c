/*
** EPITECH PROJECT, 2017
** jarvis_corrector_refill.c
** File description:
** function to refill
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

char *my_strdup(char *arg)
{
	char *res = NULL;
	int size = 0;
	int stop = 0;

	for (; stop < 2; size++)
		if (arg[size] == '\0')
			stop++;
	res = malloc(sizeof(char) * (size + 1));
	stop = 0;
	if (!res)
		return (NULL);
	for (int i = 0; stop < 2; i++) {
		if (arg[i] == '\0')
			stop++;
		res[i] = arg[i];
	}
	return (res);
}

int refill_path_in_local(char *current_path, char **arg, int size, char *cpy)
{
	int inc = 0;
	int inc_arg = 0;
	char *save = my_strdup(*arg);

	free(*arg);
	*arg = malloc(sizeof(char) * (size + 2));
	if (*arg == NULL)
		return (1);
	(*arg)[size] = '\0';
	for (; cpy[inc] != '\0'; inc++)
		(*arg)[inc] = cpy[inc];
	(*arg)[inc++] = '/';
	for (; save[inc_arg] != '\0'; inc_arg++);
	inc_arg += 1;
	for (; save[inc_arg] != '\0'; inc_arg++)
		(*arg)[inc++] = save[inc_arg];
	free(save);
	return (0);
}

int refill_path_no_local(char *current_path, char **arg, int size, char *cpy)
{
	int inc = 0;
	int inc_arg = 0;
	char *save = my_strdup(*arg);

	free(*arg);
	size += strlen(current_path);
	*arg = malloc(sizeof(char) * (size + 2));
	if (*arg == NULL)
		return (1);
	(*arg)[size] = '\0';
	for (int a = 0; current_path[a] != '\0'; a++)
		(*arg)[inc++] = current_path[a];
	for (int b = 0; cpy[b] != '\0'; b++)
		(*arg)[inc++] = cpy[b];
	(*arg)[inc++] = '/';
	for (; save[inc_arg] != '\0'; inc_arg++);
	inc_arg += 1;
	for (; save[inc_arg] != '\0'; inc_arg++)
		(*arg)[inc++] = save[inc_arg];
	free(save);
	return (0);
}

int refill_arg(char **arg, char *cpy, char *current_path, int size_after)
{
	int size = strlen(cpy) + size_after;
	int inc = 0;
	int inc_arg = 0;
	char *save = my_strdup(*arg);

	if (!(strcmp("./", current_path))) {
		if (refill_path_in_local(current_path, arg, size, cpy))
			return (free_return_nb(&save, NULL, NULL, 1));
	} else {
		if (refill_path_no_local(current_path, arg, size, cpy))
			return (free_return_nb(&save, NULL, NULL, 1));
	}
	free(save);
	return (0);
}