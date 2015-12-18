/*
** path.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Fri Dec 18 16:13:11 2015 Guillaume PROQUIN
** Last update Fri Dec 18 16:24:15 2015 Guillaume PROQUIN
*/

#include "mysh.h"

int		is_path(char *name)
{
  int		i;
  struct stat	sb;

  i = -1;
  while (name[++i] && name[i] != '/');
  return (name[i] == '/');
}

int		is_valid_path(char *path)
{
  struct stat	sb;

  return(path && access(path, X_OK) == 0 \
	 && stat(path, &sb) == 0 && S_ISREG(sb.st_mode));
}

char	*get_path(t_env *env)
{
  char	*ret;

  if (!get_env("PATH", env))
    return ("");
  ret = mem_alloc(my_strlen(get_env("PATH", env)) + 2);
  my_strcpy(ret, get_env("PATH", env));
  if (ret[0] && ret[my_strlen(ret) - 1] != ':')
    ret[my_strlen(ret)] = ':';
  return (ret);
}

char	*get_cmd_path(char *name, t_env *env)
{
  int	i;
  int	j;
  char	*path;
  char	*test;
  struct stat sb;

  if (!(path = get_path(env)))
    return (NULL);
  test = mem_alloc(my_strlen(path) + my_strlen(name) + 2);
  i = -1;
  j = -1;
  while (path[++i])
    {
      test[++j] = path[i];
      test[j + 1] = 0;
      if (path[i] == ':')
	{
	  test[j] = '/';
	  if (access(my_strcat(test, name), X_OK) == 0 && stat(test, &sb) == 0)
	    if (S_ISREG(sb.st_mode))
	      return (test);
	  j = -1;
	}
    }
  return (NULL);
}
