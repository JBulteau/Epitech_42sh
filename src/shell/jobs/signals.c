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
	struct sigaction act;

	list_jobs = malloc(sizeof(jobs_t));
	if (memset(&act, '\0', sizeof(act) + 1) == NULL || \
list_jobs == NULL)
		return (-1);
	list_jobs->pid_job = malloc(sizeof(int) * 2);
	if (list_jobs->pid_job == NULL)
		return (perror("Malloc"), -1);
	list_jobs->pid_job[0] = 0;
	list_jobs->running = false;
	list_jobs->next = NULL;
	act.sa_sigaction = (void *)catch_ctrl_z;
	sigaction(SIGTSTP, &act, NULL);
	act.sa_sigaction = (void *)catch_ctrl_c;
	sigaction(SIGINT, &act, NULL);
	return (0);
}

void free_jobs(void)
{
	jobs_t *node;

	node = list_jobs->next;
	for (int i = 0; list_jobs->pid_job[i] != 0; i++)
		kill(list_jobs->pid_job[i], SIGKILL);
	free(list_jobs->pid_job);
	free(list_jobs);
	list_jobs = node;
}