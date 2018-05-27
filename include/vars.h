/*
** EPITECH PROJECT, 2017
** vars.h
** File description:
** Vars operations
*/

#ifndef __OPE_VARS__
#define __OPE_VARS__

#include "minishell.h"

typedef enum {
	ERR = -1,
	PLUS_PLUS,
	MINUS_MINUS,
	PLUS,
	MINUS,
	MUL,
	DIV,
	MOD
} ope_t;

int ptr_plusplus(char *name, int n, shell_t *shell);
int ptr_plus(char *name, int n, shell_t *shell);
int ptr_minmin(char *name, int n, shell_t *shell);
int ptr_min(char *name, int n, shell_t *shell);
int ptr_mul(char *name, int n, shell_t *shell);
int ptr_div(char *name, int n, shell_t *shell);
int ptr_mod(char *name, int n, shell_t *shell);
ope_t find_ope(char *arg);
char *get_var_name(char *arg, int *j);
ope_t get_op(char *arg, int *j);
int get_num(char *arg, int *j);


static const struct {
	char *op_txt;
	ope_t op;
	int (*fnc)(char *name, int n, shell_t *shell);
} vars_ope[] = {
	{"++", PLUS_PLUS, &ptr_plusplus},
	{"--", MINUS_MINUS, &ptr_minmin},
	{"+=", PLUS, &ptr_plus},
	{"-=", MINUS, &ptr_min},
	{"*=", MUL, &ptr_mul},
	{"/=", DIV, &ptr_div},
	{"%=", MOD, &ptr_mod},
	{NULL, -1, NULL}
};

#endif
