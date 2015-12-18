##
## Makefile for mysh in /home/proqui_g/PSU_2015_minishell1
## 
## Made by Guillaume PROQUIN
## Login   <proqui_g@epitech.net>
## 
## Started on  Tue Nov 24 08:48:28 2015 Guillaume PROQUIN
## Last update Fri Dec 18 16:20:50 2015 Guillaume PROQUIN
##

NAME		= mysh

SRCS		= src/mysh.c		\
		src/get_next_line.c	\
		src/cmd.c		\
		src/builtin.c		\
		src/utils.c		\
		src/env.c		\
		src/parser.c		\
		src/pipe.c		\
		src/exec.c		\
		src/path.c

OBJS		= $(SRCS:.c=.o)

LIBS		= -L lib/ -lmy

CFLAGS		= -I include/

CC		= gcc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LIBS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

dbg:		CFLAGS += -g
dbg:		re

strict:		CFLAGS += -W -Wall -Werror -Wextra
strict:		re
