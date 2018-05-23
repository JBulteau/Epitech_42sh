/*
** EPITECH PROJECT, 2017
** handler_time.c
** File description:
** Handler time
*/

#include <stdio.h>
#include <time.h>
#include "prompt.h"
#include "minishell.h"
#include "my.h"

int ptr_handle_hour_24(shell_t *shell, char *input)
{
	time_t t = time(NULL);
	struct tm tm;

	UNUSED(input);
	UNUSED(shell);
	if (t != -1)
		tm = *localtime(&t);
	else
		return (ERROR_RETURN);
	printf("%02d", tm.tm_hour);
	return (SUCCESS_RETURN);
}

int ptr_handle_hour_12(shell_t *shell, char *input)
{
	time_t t = time(NULL);
	struct tm tm;

	UNUSED(input);
	UNUSED(shell);
	if (t != -1)
		tm = *localtime(&t);
	else
		return (ERROR_RETURN);
	printf("%02d", (tm.tm_hour % 13) + 1);
	return (SUCCESS_RETURN);
}

int ptr_handle_time_24(shell_t *shell, char *input)
{
	time_t t = time(NULL);
	struct tm tm;

	UNUSED(input);
	UNUSED(shell);
	if (t != -1)
		tm = *localtime(&t);
	else
		return (ERROR_RETURN);
	printf("%d:%d", tm.tm_hour, tm.tm_min);
	return (SUCCESS_RETURN);
}

int ptr_handle_time_12(shell_t *shell, char *input)
{
	time_t t = time(NULL);
	struct tm tm;

	UNUSED(input);
	UNUSED(shell);
	if (t != -1)
		tm = *localtime(&t);
	else
		return (ERROR_RETURN);
	printf("%d:%d", (tm.tm_hour % 13) + 1, tm.tm_min);
	return (SUCCESS_RETURN);
}

int ptr_handle_sec(shell_t *shell, char *input)
{
	time_t t = time(NULL);
	struct tm tm;

	UNUSED(input);
	UNUSED(shell);
	if (t != -1)
		tm = *localtime(&t);
	else
		return (ERROR_RETURN);
	printf("%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return (SUCCESS_RETURN);
}