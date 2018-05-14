/*
** EPITECH PROJECT, 2017
** get_next_line.c
** File description:
** get_next_line.c
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void save_fnc(char *save, char *src)
{
	int index;

	for (index = 0; src[index] && src[index] != '\n'; index++);
	if (!src[index])
		return;
	src[index++] = 0;
	for (int i = 0; src[index + i] && src[index + i] != '\n'; i++) {
		save[i] = src[index + i];
		src[index + i] = 0;
	}
}

static char *last_step(char *res, char *save, int index)
{
	save_fnc(save, res);
	if (res[0] == 0 && save[0] == 0 && index == 0) {
		free(res);
		return (NULL);
	}
	return (res);
}

char *gnl(int fd)
{
	static char save[READ_SIZE + 1];
	char buff[READ_SIZE];
	char *res = malloc(1);
	int index = 1;

	if (res == NULL || memset(buff, 0, sizeof(READ_SIZE)) == NULL)
		return (NULL);
	res[0] = 0;
	if ((res = concat(save, res, 0, 1)) == NULL)
		return (NULL);
	for (int i = 0; i < READ_SIZE; i++)
		save[i] = 0;
	while (index_of(res, '\n') == -1 && \
(index = read(fd, buff, READ_SIZE))) {
		buff[index] = 0;
		if ((res = concat(res, buff, 1, 0)) == NULL)
			return (NULL);
		if (index_of(buff, '\n') != -1)
			break;
	}
	return (last_step(res, save, index));
}
