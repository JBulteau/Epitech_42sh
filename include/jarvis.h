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
#include <glob.h>

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
char *free_return_pointer(char **to_free, char *to_return);
int free_ret_nb(char **to_free, char **to_free_2, glob_t *pglob, int nb);
void put_back_last_slash(char **arg);
int put_back_ending_slash(int pos, char **arg, int to_know);
int remove_mutliple_ending_slash(char **arg);
int success_case(int *pos, char **cpy_path, int *size_check, char **arg);
int before_correct(char *cpy, char **arg, glob_t *pglob, char *concat_path_star);
int check_lenght(glob_t *glob, char *curr_path, char **result, int i);
void prepare_refill(jarg_t *corr, comm_t *comm, int *nb_change, int *nb_total);
int is_slash_ending(char **arg);
int check_slash(char **arg, int i);
int refill_last(char **arg, char *cpy, char *current_path);
int misspell_process(char **arg, int *pos, char *current_path, int check);
char *final_check_path(char *path, int nb_to_path, char **arg, jarg_t *corr);
int refill_arg(char **arg, char *cpy, char *current_path, int size_after);
int check_same(char **distance_allowed, int letter_in_a_row, int i, int b);
int count_correct_letter(int dist_allow, char **both);
int correct_short(char **result, glob_t *pglob, char *curr_path);
int correct_long(char **result, glob_t *glob, char *curr_path);
char *prepare_copy(char **arg, char *current_path);
int is_slash_ending(char **arg);
int is_number_or_letter(char **arg, int pos);
void fill_infos(comm_t *comm, jarg_t *corr, int i, int *nb_argv);
void free_jarvis_corrector(jarg_t **corr, int i);
int misspell_handle(jarg_t *corr, comm_t *comm);
int refill_comm_struct(comm_t *comm, jarg_t *corr);
int jarvis_corrector(comm_t *comm, char ***env, int which, char *filepath);
jarg_t *init_struct_jarg(comm_t *comm);
int wrong_spaces_handle(comm_t *comm, jarg_t *corr);
int try_concat(comm_t *comm, jarg_t *corr, int *which_inc, int *i);

#endif