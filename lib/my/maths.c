/*
** EPITECH PROJECT, 2017
** maths.c
** File description:
** maths functions for lib
*/

int my_abs(const int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int my_pow(const int x, const int pow)
{
	int res = x;

	if (pow == 0)
		return (1);
	else if (pow == 1)
		return (x);
	for (int i = 1; i < pow; i++)
		res = res * x;
	return (res);
}