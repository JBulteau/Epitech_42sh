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

jobs_t *list_jobs;

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
	name[size - 1] = '\0';
	close(fd);
	return (name);
}

void catch_ctrl_z(int sig)
{
	jobs_t *node = find_node_job();
	char *name;

	printf("\033[2D  \033[2D");
	fflush(stdout);
	if (node->running == false)
		return;
	printf("\n[%d]", get_nb_job());
	for (int i = 0; node->pid_job[i] != 0; i++) {
		if (kill(node->pid_job[i], SIGSTOP) == -1) {
			perror("kill");
			return;
		}
		name = get_proc_name(node->pid_job[i]);
		printf("\t%d - %s -> suspended\n", node->pid_job[i], name);
		free(name);
	}
	fflush(stdout);
	if (raise(SIGCONT) == -1) {
		perror("raise");
		return;
	}
	node->running = false;
}

void catch_ctrl_c(int sig)
{
	jobs_t *node = find_node_job();

	if (node->running == false) {
		printf("\033[2D  \n");
		disp_prompt();
	} // SIGINT TO ALL CHILD FOR REAL CTRL C
}

int init_signal(void)
{
	struct sigaction act_z;
	struct sigaction act_c;

	list_jobs = malloc(sizeof(jobs_t));
	if (memset(&act_z, '\0', sizeof(act_z) + 1) == NULL || \
memset(&act_c, '\0', sizeof(act_z) + 1) == NULL || list_jobs == NULL)
		return (-1);
	list_jobs->pid_job = malloc(sizeof(int) * 2);
	if (list_jobs->pid_job == NULL)
		return (perror("Malloc"), -1);
	list_jobs->running = false;
	list_jobs->next = NULL;
	act_z.sa_sigaction = (void *)catch_ctrl_z;
	act_c.sa_sigaction = (void *)catch_ctrl_c;
	sigaction(SIGTSTP, &act_z, NULL);
	sigaction(SIGINT, &act_c, NULL);
	return (0);
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
		remove_node();
	else
		set_node_running_false();
	return (WEXITSTATUS(status));
}