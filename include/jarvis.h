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
int jarvis_corrector_built(comm_t *comm);
int free_glob_and_path(glob_t *glob, char **path);
int glob_creation(glob_t *pglob, char **path, int i);
int glob_handling(char **path, glob_t *glob);
int is_correct(comm_t *comm, glob_t glob);
void prepare_try_rm(int pos, char *result, char *try);
char *substitute_letter_no_local(char **result, glob_t *glob);
char *remove_letter_no_local(char **result, glob_t *pglob);
void prepare_try(int pos, char *result, char *try);
int test_if_exist_no_local(char *result, glob_t *pglob);
char *add_letter_no_local(char **result, glob_t *glob);
int correct_short_no_local(char **result, glob_t *pglob);
int size_before_slash(char *str);
int misspell_handle_comm_no_local(comm_t *comm, glob_t glob);
int jarvis_corrector_no_local(comm_t *comm, char ***env);
char *check_path_argv(char **arg, jarg_t *corr);
int jarvis_corrector_local_command(comm_t *comm);
int loop_number(char **try, int *pos_ind, glob_t *glob, char *curr_path);
int loop_letter(char **try, int *pos_ind, glob_t *pglob, char *curr_path);
char *substitute_letter(char **result, glob_t *pglob, char *curr_path);
int test_if_exist(char *result, glob_t *pglob, char *curr_path);
char *remove_letter(char **rsesult, glob_t *pglob, char *curr_path);
char *add_letter(char **result, glob_t *pglob, char *curr_path);
char *switch_two_adj_letter(char **result, glob_t *pglob, char *curr_path);
char *free_return_pointer(char **to_free, char *to_return);
int free_ret_nb(char **to_free, char **to_free_2, glob_t *pglob, int nb);
void put_back_last_slash(char **arg);
int put_back_ending_slash(int pos, char **arg, int to_know);
int remove_mutliple_ending_slash(char **arg);
int success_case(int *pos, char **cpy_path, int *size_check, char **arg);
int before_correct(char *cpy, char **arg, glob_t *pglob, char *);
int check_lenght(glob_t *glob, char *curr_path, char **result, int i);
void prepare_refill(jarg_t *corr, comm_t *comm, int *nb_change, int *nb_total);
int is_slash_ending(char **arg);
int check_slash(char **arg, int i);
int refill_last(char **arg, char *cpy, char *current_path);
int misspell_process(char **arg, int *pos, char *current_path, int check);
char *final_check_path(char *path, char **arg, jarg_t *corr);
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
int jarvis_corrector(comm_t *comm, char ***env);
jarg_t *init_struct_jarg(comm_t *comm);
int wrong_spaces_handle(comm_t *comm, jarg_t *corr);
int try_concat(jarg_t *corr, int *which_inc, int *i);

#endif