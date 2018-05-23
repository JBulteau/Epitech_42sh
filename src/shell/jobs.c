/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** jobs functions
*/

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

int find_last_pid(void)
{
	int i = 0;

	for (; pid_job[i] != -1 && pid_job[i] != -2; i++);
	if (i > 0)
		i--;
	return (i);
}

int remove_last_pid(void)
{
	int i = find_last_pid();

	pid_job = realloc(pid_job, sizeof(pid_t) * (i + 2));
	if (pid_job == NULL)
		return (-1);
	pid_job[i] = -2;
	return (0);
}

int add_to_pid(pid_t child)
{
	int i = find_last_pid();

	pid_job = realloc(pid_job, sizeof(pid_t) * (i + 3));
	if (pid_job == NULL)
		return (-1);
	if (pid_job[i] != -1 && pid_job[i] != -2)
		i++;
	pid_job[i] = child;
	pid_job[i + 1] = -1;
	return (0);
}