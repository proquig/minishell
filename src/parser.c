/*
** parser.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Dec 15 22:53:15 2015 Guillaume PROQUIN
** Last update Fri Dec 18 10:12:15 2015 Guillaume PROQUIN
*/

#include "mysh.h"

int		is_delimiter(char c, char *dels)
{
  int		i;

  i = -1;
  while (dels[++i] && dels[i] != c);
  return (dels[i] ? 1 : 0);
}

int		count_cmds(char *line, char *dels)
{
  int		i;
  int		count;

  count = 0;
  i = -1;
  while (line[++i])
    if (!is_delimiter(line[i], dels) \
        && (is_delimiter(line[i + 1], dels) || !line[i + 1]))
      count++;
  return (count);
}

char		**get_cmds(char *str, char *dels)
{
  int		i;
  int		j;
  int		k;
  int		word_size;
  char		**tab;

  tab = malloc(sizeof(char*) * (count_cmds(str, dels) + 1));
  i = -1;
  while (is_delimiter(str[++i], dels));
  j = 0;
  while (str[i])
    {
      word_size = i - 1;
      while (str[++word_size] && !is_delimiter(str[word_size], dels));
      if (!tab || (tab[j] = malloc(sizeof(char) * (word_size - i + 1))) == NULL)
	return (NULL);
      k = 0;
      while (str[i] && !is_delimiter(str[i], dels))
        tab[j][k++] = str[i++];
      tab[j++][k] = '\0';
      while (str[i] && is_delimiter(str[i], dels))
        i++;
    }
  tab[j] = NULL;
  return (tab);
}

int		parse_input(char *cmd, t_sh *sh)
{
  char		**cmds;
  int		i;

  i = -1;
  cmds = get_cmds(cmd, END_DEL);
  if (cmds[1])
    {
      while (cmds[++i])
	select_exec(cmds[i], sh);
      free(cmds);
    }
  else
    select_exec(cmd, sh);
}
