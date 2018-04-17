/*
** EPITECH PROJECT, 2017
** my_put.c
** File description:
** Functions that put
*/

#include <unistd.h>
#include "my.h"

int my_putchar(const char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

int my_putstr(const char *str)
{
	if (str == NULL)
		return (-1);
	return (write(STDOUT_FILENO, str, my_strlen(str)));
}

int my_puterror(char const *error)
{
	if (error == NULL)
		return (-1);
	return (write(STDERR_FILENO, error, my_strlen(error)));
}

int my_putnbr(int nb)
{
	int digits = (nb < 0) && (nb = -nb) && my_putchar('-');

	if (nb / 10)
		digits += my_putnbr(nb / 10);
	my_putchar(nb % 10 + '0');
	return (++digits);
}

int my_putnbr_base(int nb, const char *base)
{
	int b_len = my_strlen(base);
	int digits = (nb < 0) && (nb = -nb) && my_putchar('-');

	if (nb / b_len)
		digits += my_putnbr(nb / b_len);
	my_putchar(base[nb % b_len]);
	return (++digits);
	return (0);
}