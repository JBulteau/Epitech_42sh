/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions is_quote
*/

#include "my.h"
#include "parsing.h"

int is_magic(char c)
{
	return (c == '`');
}

int is_double(char c)
{
	return (c == '"');
}

int is_simple(char c)
{
	return (c == '\'');
}

int is_a_quote(char c)
{
	return (is_simple(c) || is_double(c) || is_magic(c));
}