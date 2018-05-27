/*
** EPITECH PROJECT, 2017
** GNL
** File description:
** GNL
*/

#include "my.h"
#include <stdlib.h>
#include <unistd.h>

static char *fill_buffer(char *buf, char *ptr)
{
	int i;
	int j;
	char *new_buf;

	for (i = 0; ptr[i] != '\0'; i++);
	for (j = 0; buf[j] != '\0'; j++);
	new_buf = malloc(sizeof(char) * (i + j));
	if (new_buf == NULL) {
		free(buf);
		return (NULL);
	}
	for (int k = 0; k < i + j; k++) {
		if (k < i)
			new_buf[k] = ptr[k];
		else
			new_buf[k] = buf[k - i];
	}
	free(buf);
	return (new_buf);
}

static char *my_realloc(char *buf, int n, int j)
{
	char *new_buf = malloc(sizeof(char) * n * (j + 1));

	if (new_buf == NULL) {
		free(buf);
		return (NULL);
	}
	for (int i = 0; i < n * j; i++)
		new_buf[i] = buf[i];
	for (int i = n * j; i < n * (j + 1); i++)
		new_buf[i] = '\0';
	free(buf);
	return (new_buf);
}

static int find_line_break(char *buf, int index)
{
	for (int i = 0; i < index; i++) {
		if (buf[i] == '\n' || buf[i] == '\0')
			return (0);
	}
	return (1);
}

static char *read_file(int fd, char *ptr)
{
	char *b = malloc(sizeof(char) * (READ_SIZE + 1));
	int i[2] = {0, 0};
	static int index = 0;

	if (b == NULL || fd < 0)
		return (NULL);
	for (int k = 0; k <= READ_SIZE; k++)
		b[k] = '\0';
	if (index != 0 && !(find_line_break(ptr, index)))
		return (b);
	do {
		for (b = my_realloc(b, READ_SIZE, i[0]); b == NULL;)
			return (NULL);
		for (;(i[1] = read(fd, &b[READ_SIZE * i[0]], READ_SIZE)) == -1;)
			return (b);
		if (i[1] <= 0 && b[0] == '\0' && ptr[0] == '\0') {
			free(b);
			return (NULL);
		}
	} while (find_line_break(b, READ_SIZE * ++(i[0])));
	return (b);
}

char *gnl(int fd)
{
	int i;
	static char ptr[READ_SIZE];
	char *buf = read_file(fd, ptr);

	if (buf != NULL) {
		if (ptr[0] != '\0')
			buf = fill_buffer(buf, ptr);
		if (buf == NULL)
			return (NULL);
		for (i = 0; buf[i] != '\0' && buf[i] != '\n'; i++);
		buf[i] = '\0';
		for (int k = 0; ptr[k] != '\0'; k++)
			ptr[k] = '\0';
	}
	return (buf);
}
