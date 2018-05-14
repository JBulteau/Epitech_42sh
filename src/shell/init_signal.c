/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** init the signals and init for jobs
*/

#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"

pid_t *pid_job;

void catch_ctrl_z(int sig)
{
	int i = find_last_pid();

	my_putstr("\033[2D  \033[2D");
	if (pid_job[i] == -1 || pid_job[i] == -2 || \
(pid_job[i + 1] && pid_job[i + 1] == -2))
		return;
	if (kill(pid_job[i], SIGSTOP)) {
		perror("kill");
		return;
	}
	if (raise(SIGCONT) == -1) {
		perror("raise");
		return;
	}
	printf("\npid : %d -> suspend\n", pid_job[i]);
	pid_job[i + 1] = -2;
}

void catch_ctrl_c(int sig)
{
	int i = find_last_pid();

	if (pid_job[i] == -1 || pid_job[i] == -2 || \
(pid_job[i + 1] && pid_job[i + 1] == -2)) {
		my_putstr("\033[2D  \n");
		disp_prompt();
	}
}

int init_signal(void)
{
	struct sigaction act_z;
	struct sigaction act_c;

	pid_job = malloc(sizeof(int) * 2);
	if (pid_job == NULL || memset(&act_z, '\0', sizeof(act_z) + 1) == NULL || \
memset(&act_c, '\0', sizeof(act_z) + 1) == NULL)
		return (-1);
	pid_job[0] = -1;
	act_z.sa_sigaction = (void *)catch_ctrl_z;
	act_c.sa_sigaction = (void *)catch_ctrl_c;
	sigaction(SIGTSTP, &act_z, NULL);
	sigaction(SIGINT, &act_c, NULL);
	return (0);
}