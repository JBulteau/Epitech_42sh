##
## EPITECH PROJECT, 2018
## Unit Tests
## File description:
## Unit Tests
##

NAME		=	test

SRC_FOLDER	=	../src

SRC		=	$(SRC_FOLDER)/shell/parsing/is_quote.c\
			$(SRC_FOLDER)/shell/parsing/struct.c

SRC_UT		=	is_quote_functions_test.c\
			struct_functions_test.c

OBJ		=	$(SRC:.c=.o) $(SRC_UT:.c=.o)

CCTMP		=	$(SRC:.c=.gcno) $(SRC:.c=.gcda) $(SRC_UT:.c=.gcno) $(SRC_UT:.c=.gcda)

INCLUDE		=	-I ../include

CFLAGS		=	$(INCLUDE) -Wall -Wextra --coverage -fprofile-arcs -ftest-coverage -Werror


LIB_FOLDER	=	../lib/

LIB		=	-L $(LIB_FOLDER) -lmy

LDFLAGS		=	$(LIB) -lcriterion -lgcov

CC		=	cc

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(SRC) $(SRC_UT) $(CFLAGS) $(LDFLAGS)

clean:
		rm -f *.gcno *.gcda
		rm -f $(OBJ)
		rm -f $(CCTMP)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
