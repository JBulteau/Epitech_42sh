/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** init the signals and init for jobs
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"

jobs_t *list_jobs;

int is_in_list(jobs_t *node, pid_t pid)
{
	if (node->pid_job[0] == pid)
		return (1);
	for (int i = 0; node->pid_job[i] != 0; i++)
		if (node->pid_job[i] == pid)
			return (1);
	return (0);
}

char *get_proc_name(pid_t pid)
{
	char* name = malloc(sizeof(char) * 1024);
	size_t size;
	int fd;

	if (name == NULL)
		return (NULL);
	sprintf(name, "/proc/%d/cmdline", pid);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	size = read(fd, name, 1024);
	if (size <= 0)
		return (NULL);
	name[size - 1] = '\0';
	close(fd);
	return (name);
}

int wait_for_it(pid_t pid)
{
	pid_t last_pid;
	int status = 0;

	do {
		last_pid = wait(&status);
		if (!WIFSIGNALED(status))
			continue;
		if (WTERMSIG(status) == 8)
			fprintf(stderr, "Floating exception");
		else
			fprintf(stderr, strsignal(WTERMSIG(status)));
		if (WCOREDUMP(status))
			fprintf(stderr, " (core dumped)");
		fprintf(stderr, "\n");
	} while (last_pid != pid && last_pid != -1);
	if (last_pid != -1)
		remove_node(last_pid);
	else
		set_node_running_false(last_pid);
	return (WEXITSTATUS(status));
}