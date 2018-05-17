/*
** EPITECH PROJECT, 2017
** jarvis_corrector_misspel_final.c
** File description:
** functio nfor the last path of the arg
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

int check_slash(char **arg, int i)
{
	int save = i;

	for (; (*arg)[i] != '\0'; i++)
		if ((*arg)[i] != '/')
			return (0);
	(*arg)[save + 1] = '\0';
	return (1);
}

char *final_check_path(char *path, int nb_to_path, char **arg, jarg_t *corr)
{
	int usefull = 1;

	if (path == NULL)
		return (NULL);
	if ((usefull = misspell_process(arg, &usefull, path, 1)))
		return (NULL);
	for (int i = 0; (*arg)[i] != '\0'; i++)
		if ((*arg)[i] == '/')
			check_slash(arg, i);
	return (path);
}

void refill_last(char **arg, char *cpy, char *current_path)
{
	int size = strlen(current_path) + strlen(cpy);
	int inc = 0;
	int check = 0;

	for (int i = 0; (*arg)[i] != '\0'; i++)
		if ((*arg)[i] == '/')
			check = check_slash(arg, i);
	free (*arg);
	if (check == 1)
		size += 1;
	*arg = malloc(sizeof(char) * (size + 1));
	(*arg)[size] = '\0';
	for (; current_path[inc] != '\0'; inc++)
		(*arg)[inc] = current_path[inc];
	for(int i = 0; cpy[i] != '\0'; i++)
		(*arg)[inc++] = cpy[i];
	if (check == 1)
		(*arg)[inc] = '/';
}