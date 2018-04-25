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
	int change;
} jarg_t;

enum inc {
	WHICH_INC,
	INFOS_INC,
	COMM_INC
};

/* jarvis corrector */
void fill_infos(comm_t *comm, jarg_t *corr, int i, int *nb_argv);
void free_jarvis_corrector(jarg_t **corr, int i);
int misspell_handle(jarg_t *corr, comm_t *comm);
int refill_comm_struct(comm_t *comm, jarg_t *corr);
int jarvis_corrector(comm_t *comm, char ***env, int which, char *filepath);
jarg_t *init_struct_jarg(comm_t *comm);
int wrong_spaces_handle(comm_t *comm, jarg_t *corr);
void try_concat(comm_t *comm, jarg_t *corr, int *which_inc, int *i);

#endif