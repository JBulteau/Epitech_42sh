/*
** EPITECH PROJECT, 2017
** tokens.h
** File description:
** tokens for minishell
*/

#ifndef __TOKENS__
#define __TOKENS__

#include "minishell.h"

/*	d_left.c	*/
char *handle_d_left(char *input, comm_t *comm);
int exec_d_left(comm_t *comm);
int end_d_left(comm_t *comm);

/*	s_left.c	*/
char *handle_s_left(char *input, comm_t *comm);
int exec_s_left(comm_t *comm);
int end_s_left(comm_t *comm);

/*	d_right.c	*/
char *handle_d_right(char *input, comm_t *comm);
int exec_d_right(comm_t *comm);
int end_d_right(comm_t *comm);

/*	s_right.c	*/
char *handle_s_right(char *input, comm_t *comm);
int exec_s_right(comm_t *comm);
int end_s_right(comm_t *comm);

/*	pipe.c		*/
char *handle_pipe(char *input, comm_t *comm);
int exec_pipe(comm_t *comm);
int end_pipe(comm_t *comm);

static const struct {
	char *tk;
	char *(*fnc)(char *input, comm_t *comm);
	int (*fnc_exec)(comm_t *comm);
	int (*end_exec)(comm_t *comm);
} tokens[] = {
	{">>", &handle_d_right, &exec_d_right, &end_d_right},
	{">", &handle_s_right, &exec_s_right, &end_s_right},
	{"<<", &handle_d_left, &exec_d_left, &end_d_left},
	{"<", &handle_s_left, &exec_s_left, &end_s_left},
	{"|", &handle_pipe, NULL, NULL},
	{NULL, NULL, NULL, NULL}
};

#endif