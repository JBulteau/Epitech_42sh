/*
** EPITECH PROJECT, 2018
** jobs buildin
** File description:
** show all jobs running
*/

#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "builtins.h"

char *get_proc_name_line(jobs_t *node)
{
	char *name = NULL;
	char *rslt;

	rslt = malloc(2);
	rslt[0] = 0;
	for (int i = 0; node->pid_job[i] != 0; i++) {
		free(name);
		name = get_proc_name(node->pid_job[i]);
		rslt = realloc(rslt, strlen(rslt) + strlen(name) + 2);
		//rslt = strcat(rslt, " ");
		rslt = strcat(rslt, name);
	}
	free(name);
	return (rslt);
}

int ptr_jobs(comm_t *comm, shell_t *shell)
{
	char *name = NULL;
	jobs_t *node = list_jobs;

	node = node->next;
	for (int i = 1; node != NULL; i++) {
		name = get_proc_name_line(node);
		printf("[%d]\tsuspended\t%s\n", i, name);
		node = node->next;
		free(name);
	}
	return (0);
}