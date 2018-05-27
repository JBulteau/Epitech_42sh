/*
** EPITECH PROJECT, 2018
** jobs buildin
** File description:
** show all jobs running
*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "my.h"
#include "minishell.h"
#include "builtins.h"
#include "my.h"

char *get_proc_name_line(jobs_t *node)
{
	char *name = NULL;
	char *rslt;

	rslt = malloc(2);
	rslt[0] = 0;
	for (int i = 0; node->pid_job[i] != 0; i++) {
		free(name);
		name = get_proc_name(node->pid_job[i]);
		if (!name)
			return (NULL);
		rslt = realloc(rslt, strlen(rslt) + strlen(name) + 2);
		if (!rslt)
			return (NULL);
		rslt = strcat(rslt, strcat(name, " "));
	}
	free(name);
	return (rslt);
}

int print_line_jobs(pid_t pid, int nb)
{
	char *name;

	if (nb != 0)
		printf("\t");
	name = get_proc_name(pid);
	if (!name)
		return (ERROR_RETURN);
	printf("%d\tsuspended\t%s\n", pid, name);
	free(name);
	return (0);
}

int print_jobs_info(jobs_t *node)
{
	int err = 0;

	for (int i = 1; node != NULL; i++) {
		printf("[%d]\t", i);
		for (int nb = 0; node->pid_job[nb] != 0; nb++)
			err = print_line_jobs(node->pid_job[nb], nb);
		if (err != 0)
			return (err);
		node = node->next;
	}
	return (0);
}

int ptr_jobs(comm_t *comm, shell_t *shell)
{
	char *name = NULL;
	jobs_t *node = list_jobs;

	UNUSED(shell);
	node = node->next;
	if (comm->argv[1] && !strcmp(comm->argv[1], "-l"))
		return (print_jobs_info(node));
	for (int i = 1; node != NULL; i++) {
		name = get_proc_name_line(node);
		if (!name)
			return (ERROR_RETURN);
		printf("[%d]\tsuspended\t%s\n", i, name);
		node = node->next;
		free(name);
	}
	return (0);
}