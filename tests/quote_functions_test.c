/*
** EPITECH PROJECT, 2017
** Unit Tests
** File description:
** Unit tests for quote functions
*/

#include "my.h"
#include "parsing.h"
#include <criterion/criterion.h>

Test(quote, is_a_quote)
{
	cr_expect_eq(is_a_quote('\''), 1);
	cr_expect_eq(is_a_quote('"'), 1);
	cr_expect_eq(is_a_quote('`'), 1);
	cr_expect_eq(is_a_quote('a'), 0);
}

Test(quote, is_simple)
{
	cr_expect_eq(is_simple('\''), 1);
	cr_expect_eq(is_simple('"'), 0);
	cr_expect_eq(is_simple('`'), 0);
	cr_expect_eq(is_simple('a'), 0);
}

Test(quote, is_double)
{
	cr_expect_eq(is_double('\''), 0);
	cr_expect_eq(is_double('"'), 1);
	cr_expect_eq(is_double('`'), 0);
	cr_expect_eq(is_double('a'), 0);
}

Test(quote, is_magic)
{
	cr_expect_eq(is_magic('\''), 0);
	cr_expect_eq(is_magic('"'), 0);
	cr_expect_eq(is_magic('`'), 1);
	cr_expect_eq(is_magic('a'), 0);
}