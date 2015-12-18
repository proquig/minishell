/*
** get_next_line.h for get_next_line in /home/proqui_g/rendu/CPE_2015_get_next_line
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Nov 16 15:17:49 2015 Guillaume PROQUIN
** Last update Fri Dec  4 09:43:34 2015 Guillaume PROQUIN
*/

#ifndef		__GET_NEXT_LINE__
# define	__GET_NEXT_LINE__

# include	<unistd.h>

# ifndef	READ_SIZE
#  define	READ_SIZE 42
# endif

char		*get_next_line(const int fd);

# endif
