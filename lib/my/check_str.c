/*
** EPITECH PROJECT, 2017
** check_str.c
** File description:
** Functions that checks char * for somethings
*/

#include <unistd.h>

int is_num(const char *str)
{
	if (str == NULL)
		return (-1);
	for (int i = 0; str[i]; i++) {
		if ((i == 0) && ((str[i] == '-') || ((str[i] == '+'))))
			continue;
		if ((str[i] < '0') || (str[i] > '9'))
			return (-1);
	}
	return (0);
}

int is_alpha(const char *str)
{
	if (str == NULL)
		return (-1);
	for (int i = 0; str[i]; i++)
		if (!(((str[i] >= 'A') && (str[i] <= 'Z')) || ((str[i] >= 'a'\
) && (str[i] <= 'z'))))
			return (-1);
	return (0);
}

int is_alphanum(const char *str)
{
	if (str == NULL)
		return (-1);
	for (int i = 0; str[i]; i++)
		if (!(((str[i] >= 'A') && (str[i] <= 'Z')) || ((str[i] >= 'a'\
) && (str[i] <= 'z')) || ((str[i] >= '0') && (str[i] <= '9'))))
			return (-1);
	return (0);
}

int index_of(const char *str, const char c)
{
	if (str == NULL)
		return (-1);
	for (int i = 0; str[i]; i++)
		if (str[i] == c)
			return (i);
	return (-1);
}

int check_chars(const char *str, const char *valid)
{
	if (str == NULL || valid == NULL)
		return (-1);
	for (int i = 0; str[i]; i++) {
		if (index_of(valid, str[i]) == -1)
			return (-1);
	}
	return (0);
}