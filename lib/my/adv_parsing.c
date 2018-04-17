/*
** EPITECH PROJECT, 2017
** adv_parsing.c
** File description:
** Advenced parsing functions
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

static int adv_count_w(const char *str, const char *sep, const char \
*ign_start, const char *ign_end)
{
	int w_count = 0;
	int is_w = 0;
	int ign = -1;

	if (str == NULL || sep == NULL || ign_start == NULL || ign_end == NULL)
		return (-1);
	for (int i = 0; str[i]; i++) {
		if (ign == -1 && (ign = index_of(ign_start, str[i])) != -1) {
			w_count++;
			continue;
		} else if (ign != -1 && str[i] == ign_end[ign]) {
			ign = -1;
			continue;
		}
		if (ign == -1 && index_of(sep, str[i]) == -1) {
			w_count += (is_w == 0) ? 1 : 0;
			is_w = 1;
		} else
			is_w = 0;
	}
	return (w_count);
}

int adv_get_wlen(const char *str, const char *sep, const char \
*ign_start, const char *ign_end)
{
	int len = 0;
	int ign = index_of(ign_start, str[0]);

	if (str == NULL || sep == NULL || ign_start == NULL || ign_end == NULL)
		return (-1);
	if (ign != -1) {
		for (int i = 0; str[i] && str[i] != ign_end[ign]; i++)
			len++;
		return ((str[len] == '\0') ? -1 : len + 1);
	}
	for (int i = 0; str[i]; i++) {
		if (ign == -1 && (ign = index_of(ign_start, str[i])) != -1)
			continue;
		else if (ign != -1 && str[i] == ign_end[ign])
			break;
		if (!(ign == -1 && index_of(sep, str[i]) == -1))
			break;
		len++;
	}
	return (len);
}

char **adv_parse(const char *str, const char *sep, const char *ign_start, \
const char *ign_end)
{
	char **res = NULL;
	int w_count = adv_count_w(str, sep, ign_start, ign_end);
	int curr_w = 0;
	int ign = -1;
	int is_w = 0;

	if (str == NULL || sep == NULL || ign_start == NULL || ign_end == NULL \
|| (res = malloc(sizeof(char *) * (w_count + 1))) == NULL)
		return (NULL);
	res[w_count] = NULL;
	for (int i = 0; str[i]; i++) {
		if (ign == -1 && (ign = index_of(ign_start, str[i])) != -1) {
			curr_w++;
			res[curr_w - 1] = !(is_w) ? my_strndup(str + i, adv_\
get_wlen(str + i, sep, ign_start, ign_end)) : res[curr_w - 1];
			continue;
		} else if (ign != -1 && str[i] == ign_end[ign] && \
(ign = -1) == -1)
			continue;
		if (ign == -1 && index_of(sep, str[i]) == -1) {
			curr_w += (is_w == 0) ? 1 : 0;
			res[curr_w - 1] = !(is_w) ? my_strndup(str + i, adv_\
get_wlen(str + i, sep, ign_start, ign_end)) : res[curr_w - 1];
			is_w = 1;
		} else
			is_w = 0;
	}
	return (res);
}