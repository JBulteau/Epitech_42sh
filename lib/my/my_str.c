/*
** EPITECH PROJECT, 2017
** my_str.c
** File description:
** Str functions
*/

#include <unistd.h>
#include <stdlib.h>

int my_strlen(const char *str)
{
	int len;

	for (len = 0; str[len]; len++);
	return (len);
}

char *my_strcpy(char *dest, char const *src, int n)
{
	if (dest == NULL || src == NULL)
		return (NULL);
	for (int i = 0; n && i < n; i++)
		dest[i] = src[i];
	for (int i = 0; n == 0 && src[i]; i++)
		dest[i] = src[i];
	return (dest);
}

int my_strcmp(const char *str1, const char *str2, int n)
{
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (n == 0 && my_strlen(str1) != my_strlen(str2))
		return (1);
	for (int i = 0; n == 0 && str1[i] && str2[i]; i++)
		if (str1[i] != str2[i])
			return (1);
	for (int i = 0; i < n && str1[i] && str2[i]; i++)
		if (str1[i] != str2[i])
			return (1);
	return (0);
}

char *my_strndup(const char *str, const int n)
{
	char *res = NULL;
	int len;

	if (str == NULL)
		return (NULL);
	len = my_strlen(str);
	res = malloc(((n) ? n : len) + 1);
	if (res == NULL)
		return (NULL);
	res[(n) ? n : len] = '\0';
	return (my_strcpy(res, str, n));
}

char *my_revstr(const char *str)
{
	char *res = my_strndup(str, 0);
	int len = my_strlen(str);

	if (str == NULL)
		return (NULL);
	for (int i = 0; i < len; i++)
		res[i] = str[len - i - 1];
	return (res);
}
