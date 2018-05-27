/*
** EPITECH PROJECT, 2017
** sig_handlers.c
** File description:
** Signal handlers
*/

#include <stdio.h>
#include <signal.h>
#include "minishell.h"
#include "my.h"

static void loop_ctrl_z(jobs_t *node)
{
	char *name;

	for (int i = 0; node->pid_job[i] != 0; i++) {
		if (kill(node->pid_job[i], SIGSTOP) == -1) {
			;//perror("kill");
			return;
		}
		name = get_proc_name(node->pid_job[i]);
		printf("\t%d - %s -> suspended\n", node->pid_job[i], name);
		free(name);
	}
	fflush(stdout);
}

void catch_ctrl_z(int sig)
{
	jobs_t *node = find_node_job();

	UNUSED(sig);
	printf("\033[2D  \033[2D");
	fflush(stdout);
	if (node->running == false)
		return;
	printf("\n[%d]", get_nb_job());
	loop_ctrl_z(node);
	if (raise(SIGCONT) == -1) {
		perror("raise");
		exit(84);
	}
	node->running = false;
}