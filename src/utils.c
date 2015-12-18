/*
** utils.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell1/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Nov 30 18:17:07 2015 Guillaume PROQUIN
** Last update Mon Dec  7 00:00:11 2015 Guillaume PROQUIN
*/

#include "mysh.h"

int		count_args(char **args)
{
  int		i;

  i = 0;
  while (args[i])
    i++;
  return (i);
}

char		*mem_alloc(int size)
{
  char		*ret;
  int		i;

  if ((ret = malloc(size)) == NULL)
    {
      my_printf("%ZFailed to malloc\n", 2);
      exit(2);
    }
  i = -1;
  while (++i < size)
    ret[i] = 0;
  return (ret);
}

void		check_error(char *c, char *file, t_sh *sh)
{
  char		*m[3];
  char		*error;
  int		i;
  struct stat	sb;

  m[0] = my_strcmp("cd", c) ? "Command not found" : "No such file or directory";
  m[1] = "Permission denied";
  m[2] = NULL;
  error = NULL;
  i = -1;
  sh->status = 1;
  if (stat(file, &sb) == 0 && !S_ISDIR(sb.st_mode) && my_strcmp("cd", c) == 0)
    error = "Not a directory";
  else if (stat(file, &sb) == 0 && !S_ISREG(sb.st_mode) && my_strcmp("cd", c))
    error = m[2];
  else
    while ((error = m[++i]) && access(file, i) == 0);
  error = error ? error : m[1];
  if (error)
    my_printf("%Z%s: %s.\n", 2, file, error);
}

char	**env_to_tab(t_env *env)
{
  char	**tab;
  t_env	*start;
  int	i;

  start = env;
  i = 1;
  while (start)
    {
      start = start->next;
      ++i;
    }
  if ((tab = malloc(i * sizeof(*tab))) == NULL)
    return (NULL);
  i = -1;
  while (env)
    {
      tab[++i] = mem_alloc(my_strlen(env->name) + my_strlen(env->value) + 2);
      my_strcpy(tab[i], env->name);
      my_strcat(tab[i], "=");
      my_strcat(tab[i], env->value);
      env = env->next;
    }
  tab[i + 1] = 0;
  return (tab);
}

t_env	*env_from_tab(char **ae)
{
  int	i;
  int	j;
  int	name_size;
  t_env	*env;
  t_env	*var;
  char	*name;
  char	*value;

  env = NULL;
  i = -1;
  while (ae[++i])
    {
      j = -1;
      while (ae[i][++j] && ae[i][j] != '=');
      name_size = j;
      name = mem_alloc(name_size + 1);
      value = mem_alloc(my_strlen(&ae[i][name_size + 1]) + 1);
      my_strncpy(name, ae[i], name_size);
      my_strcpy(value, &ae[i][name_size + 1]);
      var = set_var(name, value);
      env = add_env(var, env);
    }
  return (env);
}
