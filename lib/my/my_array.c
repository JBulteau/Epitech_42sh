/*
** EPITECH PROJECT, 2017
** my_array.c
** File description:
** Array fncs
*/

#include <stdlib.h>
#include <unistd.h>

void free_array(void **array)
{
	if (array == NULL)
		return;
	for (int i = 0; array[i] != NULL; i++)
		free(array[i]);
	free(array);
}

int array_len(void **array)
{
	int len = 0;

	if (array == NULL)
		return (-1);
	while (array[len++] != NULL);
	return (len);
}