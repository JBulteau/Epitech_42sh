##
## EPITECH PROJECT, 2017
## EvalExpr
## File description:
## Lib Makefile
##

NAME = my

SRCS =	check_str.c\
	maths.c\
	my_put.c\
	my_str.c\
	my_str2.c\
	parsing.c\
	adv_parsing.c\
	my_array.c\
	my_get.c\
	gnl.c\

OBJS = $(SRCS:.c=.o)

INC = -I ../../include

CC = gcc

CFLAGS = $(INC) -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar rc lib$(NAME).a $(OBJS)
	cp lib$(NAME).a ..
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f lib$(NAME).a
	rm -f ../lib$(NAME).a

re: fclean all

debug: CFLAGS += -g
debug: re