/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** functions is_separator_char
*/

#include "my.h"
#include "parsing.h"

int is_ampersand(char c)
{
	return (c == '&');
}

int is_r_arrow(char c)
{
	return (c == '>');
}

int is_l_arrow(char c)
{
	return (c == '<');
}

int is_pipe(char c)
{
	return (c == '|');
}

int is_cmd_separator(char c)
{
	return (is_pipe(c) || is_l_arrow(c) \
	|| is_r_arrow(c) || is_ampersand(c));
}