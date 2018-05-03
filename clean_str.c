/*
** EPITECH PROJECT, 2018
** clean_str.c
** File description:
** clean all space 
*/

#include "../../include/colle.h"

char *clean_str(char *str)
{
	int begin = 0;
	int end = 0;

	if (str[begin] == '\0')
		return (str);
	for (end = 0; str[end] == ' ' || str[end] == '\t' \
|| str[end] == '\0'; end++);
	while (str[end] != '\0') {
		if (str[end] != ' ' && str[end] != '\t') {
			str[begin] = str[end];
			begin++;
		} else if ((str[end] == ' ' && str[end + 1] != ' '	\
&& str[end + 1] != '\t' && str[end + 1] != '\0') || (str[end] == '\t' \
&& str[end + 1] != ' ' && str[end + 1] != '\t' && str[end + 1] != '\0')) {
			str[begin] = ' ';
			begin++;
		}
		end++;
	}
	str[begin] = '\0';
	return (str);
}
