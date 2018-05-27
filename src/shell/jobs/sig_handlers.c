/*
** EPITECH PROJECT, 2017
** sig_handlers.c
** File description:
** Signal handlers
*/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

static void loop_ctrl_z(jobs_t *node)
{
	char *name;

	for (int i = 0; node->pid_job[i] != 0; i++) {
		if (kill(node->pid_job[i], SIGSTOP) == -1)
			return;
		name = get_proc_name(node->pid_job[i]);
		printf("\t%d - %s -> suspended\n", node->pid_job[i], name);
		free(name);
	}
	fflush(stdout);
}

void remove_node_running(void)
{
	jobs_t *node = list_jobs;
	int status = 0;

	while (node != NULL) {
		if (node->running == true) {
			//wait_for_it(node->pid_job[0]);
			wait(&status);
			remove_node(node->pid_job[0]);
			return;
		}
		else
			node = node->next;
	}
}

void catch_ctrl_c(int sig)
{
	UNUSED(sig);
	printf("\033[2D  \033[2D\n");
	fflush(stdout);
	remove_node_running();
}

void catch_ctrl_z(int sig)
{
	jobs_t *node = find_node_job();

	UNUSED(sig);
	printf("\033[2D  \033[2D");
	fflush(stdout);
	if (node->running == false) {
		printf("\n");
		return;
	}
	printf("\n[%d]", get_nb_job());
	loop_ctrl_z(node);
	if (raise(SIGCONT) == -1) {
		perror("raise");
		exit(84);
	}
	node->running = false;
}