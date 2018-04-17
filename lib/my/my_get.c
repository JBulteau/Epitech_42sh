/*
** EPITECH PROJECT, 2017
** my_get.c
** File description:
** Get functions
*/

#include <unistd.h>
#include "my.h"

int my_getnbr(char const *str)
{
	int nb = 0;
	int sign = 1;
	int i = 0;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] && (str[i] == '+' || str[i] == '-'); i++)
		if (str[i] == '-')
			sign = -sign;
	for (; str[i]; i++) {
		nb *= 10;
		nb += str[i] - '0';
	}
	return (nb * sign);
}

int my_getnbr_base(char const *str, char const *base)
{
	int nb = 0;
	int sign = 1;
	int i = 0;
	int base_l = my_strlen(base);

	if (str == NULL || base == NULL)
		return (0);
	for (i = 0; str[i] && (str[i] == '+' || str[i] == '-'); i++)
		if (str[i] == '-')
			sign = -sign;
	for (; str[i]; i++) {
		nb *= base_l;
		nb += index_of(base, str[i]);
	}
	return (nb * sign);
}