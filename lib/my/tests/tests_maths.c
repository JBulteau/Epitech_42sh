/*
** EPITECH PROJECT, 2017
** maths.c
** File description:
** Unit tests for maths functions
*/

#include "my.h"
#include <criterion/criterion.h>

Test(maths, abs)
{
	cr_expect(my_abs(-42) == 42);
	cr_expect(my_abs(42) == 42);
}

Test(maths, pow)
{
	cr_expect(my_pow(2, 2) == 4);
	cr_expect(my_pow(2, 0) == 1);
	cr_expect(my_pow(2, 1) == 2);
}