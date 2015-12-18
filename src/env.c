/*
** env.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell1
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Wed Dec  2 09:23:55 2015 Guillaume PROQUIN
** Last update Sun Dec  6 15:11:10 2015 Guillaume PROQUIN
*/

#include "mysh.h"

t_env	*set_var(char *name, char *value)
{
  t_env	*var;

  if ((var = malloc(sizeof(*var))) == NULL)
    return (NULL);
  var->name = name;
  var->value = value;
  var->prev = NULL;
  var->next = NULL;
  return (var);
}

t_env	*add_env(t_env *var, t_env *env)
{
  t_env	*start;

  env = env ? env : var;
  start = env;
  if (env != var)
    {
      while (env->next)
	env = env->next;
      env->next = var;
      var->prev = env;
    }
  return (start);
}

t_env	*del_env(char *name, t_env *env)
{
  t_env	*var;

  var = env;
  if (var)
    {
      while (my_strcmp(name, var->name) != 0 && var->next)
	var = var->next;
      env = (var == env && var->next) ? var->next : env;
      if (my_strcmp(name, var->name) == 0)
	{
	  if (var->prev)
	    var->prev->next = var->next;
	  if (var->next)
	    var->next->prev = var->prev;
	  env = env == var && !var->next ? NULL : env;
	  free(var);
	}
    }
  return (env);
}

t_env	*set_env(char *name, char *value, t_env *env)
{
  t_env	*var;

  var = env;
  if (var)
    {
      while (var->next && my_strcmp(name, var->name) != 0)
	var = var->next;
      if (my_strcmp(name, var->name) == 0)
	var->value = value;
    }
  if (!var || my_strcmp(name, var->name) != 0)
    {
      var = set_var(name, value);
      env = add_env(var, env);
    }
  return (env);
}

char	*get_env(char *name, t_env *env)
{
  while (env && my_strcmp(name, env->name) != 0)
    env = env->next;
  return (env && my_strcmp(name, env->name) == 0 ? env->value : NULL);
}
