/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** Header files for lib
*/

#ifndef __MY_H__
#define __MY_H__

/*	check_str.c	*/
int	is_num(const char *str);
int	is_alpha(const char *str);
int	is_alphanum(const char *str);
int	check_chars(const char *str, const char *valid);
int	index_of(const char *str, const char c);

/*	maths.c		*/
int	my_abs(const int x);
int	my_pow(const int x, const int pow);

/*	my_put.c	*/
int	my_putchar(const char c);
int	my_putstr(char const *str);
int	my_puterror(char const *error);
int	my_putnbr(const int nb);
int	my_putnbr_base(int nbr, char const *base);

/*	my_str.c	*/
int	my_strlen(char const *str);
char	*my_strndup(char const *src, const int n);
char	*my_strcpy(char *dest, char const *src, const int n);
int	my_strcmp(char const *s1, char const *s2, const int n);
char	*my_revstr(char *str);

/*	my_str2.c	*/
char	*find_str(char *str, char const *to_find);
char	*concat(char *str1, char *str2, int free1, int free2);
int	my_showstr(char const *str);

/*	parsing.c	*/
char **strwordarr(const char *str, const char *sep);
int get_wlen(const char *str, const char *sep);

/*	adv_parsing.c	*/
char 	**adv_parse(const char *str, const char *delim, \
const char *ignore_start, const char *ignore_end);
int adv_get_wlen(const char *str, const char *sep, const char \
*ign_start, const char *ign_end);

/*	my_array.c	*/
void	free_array(void **array);
int	array_len(void **array);

/*	gnl.c		*/
char	*gnl(const int fd);

/*	my_get.c	*/
int	my_getnbr(char const *str);
int	my_getnbr_base(char const *str, char const *base);

#define	READ_SIZE	1
#define	SUCCESS_CODE	0
#define	ERROR_CODE	84
static const char	HEX_UP[]	=	"0123456789ABCDEF";
static const char	HEX_LOW[]	=	"0123456789abcdef";
static const char	NUM[]		=	"0123456789";
static const char	ALPHA_LOW[]     =	"abcdefghijklmnopqrstuvwxyz";
static const char	ALPHA_UP[]      =	"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

#endif