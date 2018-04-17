/*
** EPITECH PROJECT, 2017
** parsing.c
** File description:
** Parsing fncs
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

static int count_w(const char *str, const char *sep)
{
	int w_count = 0;
	int is_w = 0;

	if (str == NULL || sep == NULL)
		return (-1);
	for (int i = 0; str[i]; i++) {
		if (index_of(sep, str[i]) == -1) {
			w_count += (is_w == 0) ? 1 : 0;
			is_w = 1;
		} else {
			is_w = 0;
			continue;
		}
	}
	return (w_count);
}

int get_wlen(const char *str, const char *sep)
{
	int len = 0;

	if (str == NULL || sep == NULL)
		return (-1);
	for (int i = 0; str[i++]; len++) {
		if (index_of(sep, str[i]) != -1)
			return (len + 1);
	}
	return (len);
}

char **strwordarr(const char *str, const char *sep)
{
	char **res = NULL;
	int w_count = count_w(str, sep);
	int is_w = 0;
	int curr_w = 0;

	if (str == NULL || sep == NULL)
		return (NULL);
	res = malloc(sizeof(char *) * (w_count + 1));
	res[w_count] = NULL;
	for (int i = 0; str[i]; i++) {
		if (index_of(sep, str[i]) == -1) {
			curr_w += !(is_w) ? 1 : 0;
			res[curr_w - 1] = !(is_w) ? \
my_strndup(str + i, get_wlen(str + i, sep)) : res[curr_w - 1];
			is_w = 1;
		} else {
			is_w = 0;
			continue;
		}
	}
	return (res);
}