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
int exec_d_left(comm_t *comm);
int end_d_left(comm_t *comm);

/*	s_left.c	*/
int exec_s_left(comm_t *comm);
int end_s_left(comm_t *comm);

/*	d_right.c	*/
int exec_d_right(comm_t *comm);
int end_d_right(comm_t *comm);

/*	s_right.c	*/
int exec_s_right(comm_t *comm);
int end_s_right(comm_t *comm);

/*	pipe.c		*/
int exec_pipe(comm_t *comm);
int end_pipe(comm_t *comm);

static const struct {
	char *tk;
	int (*fnc_exec)(comm_t *comm);
	int (*end_exec)(comm_t *comm);
} tokens[] = {
	{"<", &exec_s_left, &end_s_left},
	{"<<", &exec_d_left, &end_d_left},
	{">", &exec_s_right, &end_s_right},
	{">>", &exec_d_right, &end_d_right},
	{NULL, NULL, NULL}
};

#endif