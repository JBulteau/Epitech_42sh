/*
** EPITECH PROJECT, 2017
** jarvis.h
** File description:
** header for jarvis
*/

#ifndef __JARVIS__
#define __JARVIS__

#include "my.h"
#include "minishell.h"

typedef struct {
	char *name;
	int pos;
	int correct;
} args_t;

typedef struct {
	int nb_good_start;
	args_t *infos;
	int nb_good_end;
	int *which;
} jcorr_t;

/* jarvis corrector.c */
int jarvis_corrector(comm_t * comm, char ***env, int which, char *filepath);
int more_than_two_argv_handling(comm_t *comm, char *filepath, char **env);

#endif