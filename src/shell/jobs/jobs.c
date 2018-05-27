/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** jobs functions
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "minishell.h"

jobs_t *find_node_job(void)
{
	jobs_t *new = list_jobs;

	while (new->next != NULL)
		new = new->next;
	return (new);
}

int get_nb_job(void)
{
	int i = 0;
	jobs_t *new = list_jobs;

	for (; new->next != NULL; i++, new = new->next);
	return (i);
}

jobs_t *new_node(void)
{
	jobs_t *new;
	jobs_t *node = find_node_job();

	new = malloc(sizeof(jobs_t));
	if (new == NULL)
		return (perror("Malloc"), NULL);
	new->pid_job = malloc(sizeof(int) * 2);
	if (new->pid_job == NULL)
		return (perror("Malloc"), NULL);
	new->pid_job[0] = 0;
	new->running = true;
	new->next = NULL;
	node->next = new;
	return (new);
}

void remove_node(pid_t pid)
{
	jobs_t *node = list_jobs->next;
	jobs_t *prev = list_jobs;

	while (node && is_in_list(node, pid) == 0) {
		prev = node;
		node = node->next;
	}
	if (!node)
		return;
	if (node->next != NULL)
		prev->next = node->next;
	else
		prev->next = NULL;
	free(node->pid_job);
	free(node);
}

int add_pid_jobs(pid_t child)
{
	int i = 0;
	jobs_t *node = find_node_job();

	for (; node->pid_job[i] != 0; i++);
	node->pid_job = realloc(node->pid_job, sizeof(int) * (i + 2));
	if (node->pid_job == NULL) {
		perror("Realloc");
		return (-1);
	}
	node->pid_job[i] = child;
	node->pid_job[i + 1] = 0;
	return (0);
}