/*
** EPITECH PROJECT, 2017
** my_str2.c
** File description:
** Str functions 2
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char	*find_str(char *haystack, char const *needle)
{
	int len_n = my_strlen(needle);
	int cursor = 0;

	for (int i = 0; haystack[i]; i++) {
		if (haystack[i] == needle[cursor])
			cursor++;
		if (len_n == cursor)
			return (haystack + i - len_n + 1);
	}
	return (NULL);
}

char	*concat(char *str1, char *str2, int free1, int free2)
{
	char *res = NULL;
	int len1 = my_strlen(str1);
	int len2 = my_strlen(str2);

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	res = malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	for (int i = 0; i < len1; i++)
		res[i] = str1[i];
	for (int i = 0; i < len2; i++)
		res[len1 + i] = str2[i];
	res[len1 + len2] = '\0';
	if (free1)
		free(str1);
	if (free2)
		free(str2);
	return (res);
}

int	my_showstr(char const *str)
{
	int digits = 0;

	for (int i = 0; str[i]; i++)
		if (str[i] >= 32 && str[i] != 127)
			digits += my_putchar(str[i]);
		else {
			digits += my_putchar('\\');
			digits += my_putnbr_base(str[i], HEX_UP);
		}
	return (digits);
}