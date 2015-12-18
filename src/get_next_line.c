/*
** get_next_line.c for get_next_line.c in /home/proqui_g/rendu/CPE_2015_get_next_line
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Nov 16 15:18:06 2015 Guillaume PROQUIN
** Last update Thu Dec  3 11:28:04 2015 Guillaume PROQUIN
*/

#include <stdlib.h>
#include "get_next_line.h"

int		bufflen(char *buff)
{
  int		i;

  i = -1;
  while (buff[++i]);
  return (i);
}

char		*buff_cat(char *res, char *buff)
{
  int		i;
  int		j;
  char		*ret;

  i = -1;
  j = -1;
  res = res ? res : "";
  if ((ret = malloc(bufflen(buff) + bufflen(res) + 1)) == NULL)
    return (NULL);
  while (++i < bufflen(buff))
    ret[++j] = buff[i];
  i = -1;
  while (++i < bufflen(res))
    ret[++j] = res[i];
  ret[++j] = 0;
  return (ret);
}

char		*get_next_line(const int fd)
{
  int		i;
  int		j;
  int		size;
  char		buf[READ_SIZE + 1];
  static char	buffer[READ_SIZE] = {0};

  i = -1;
  j = -1;
  size = -1;
  if (buffer[0])
    while (buffer[++size]);
  else
    if ((size = read(fd, buffer, READ_SIZE)) < 1 || READ_SIZE < 1)
      return (NULL);
  while (++i < size && buffer[i] != '\n')
    buf[i] = buffer[i];
  buf[i] = 0;
  if (buffer[i] == '\n')
    {
      while (++i < size)
	buffer[++j] = buffer[i];
      buffer[++j] = 0;
    }
  buffer[0] = j == -1 ? 0 : buffer[0];
  return (buff_cat(!(i == size) || j != -1 ? "" : get_next_line(fd), buf));
}
