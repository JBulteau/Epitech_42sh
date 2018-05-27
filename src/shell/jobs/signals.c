/*
** EPITECH PROJECT, 2017
** signals.c
** File description:
** Signal functions
*/

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "minishell.h"

int init_signal(void)
{
	struct sigaction act_z;

	list_jobs = malloc(sizeof(jobs_t));
	if (memset(&act_z, '\0', sizeof(act_z) + 1) == NULL || \
list_jobs == NULL)
		return (-1);
	list_jobs->pid_job = malloc(sizeof(int) * 2);
	if (list_jobs->pid_job == NULL)
		return (perror("Malloc"), -1);
	list_jobs->pid_job[0] = 0;
	list_jobs->running = false;
	list_jobs->next = NULL;
	act_z.sa_sigaction = (void *)catch_ctrl_z;
	sigaction(SIGTSTP, &act_z, NULL);
	return (0);
}

void free_jobs(void)
{
	jobs_t *node;

	node = list_jobs->next;
	for (int i = 0; list_jobs->pid_job[i] != 0; i++)
		if (kill(list_jobs->pid_job[i], SIGKILL))
			;//perror("kill");
	free(list_jobs->pid_job);
	free(list_jobs);
	list_jobs = node;
}