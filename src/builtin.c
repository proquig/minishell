/*
** builtin.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell1
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Nov 30 10:28:07 2015 Guillaume PROQUIN
** Last update Sun Dec  6 22:20:09 2015 Guillaume PROQUIN
*/

#include "mysh.h"

t_sh	*fn_cd(char *cmd, t_sh *sh)
{
  char	**args;
  int	nb_args;
  int	status;

  args = my_str_to_wordtab(cmd);
  nb_args = count_args(&args[1]);
  args[1] = args[1] ? args[1] : get_env("HOME", sh->env);
  args[1] = args[1] && my_strcmp("-", args[1]) == 0 ? sh->old_pwd : args[1];
  if (nb_args <= 1)
    if (args[1] && (status = chdir(args[1])) != 0)
      check_error(args[0], args[1], sh);
    else
      set_path(args[1], sh);
  else
    {
      sh->status = 1;
      my_printf("%Z%s: Too many arguments.\n", 2, args[0]);
    }
  free(args);
  return (sh);
}

t_sh	*fn_setenv(char *cmd, t_sh *sh)
{
  char	**args;
  int	nb_args;
  char	*error;

  error = NULL;
  args = my_str_to_wordtab(cmd);
  nb_args = count_args(&args[1]);
  if (!nb_args)
    return (fn_env(cmd, sh));
  if (nb_args == 1 || nb_args == 2)
    if (!IS_MIN(args[1][0]) && !IS_MAJ(args[1][0]))
      error = "Variable name must begin with a letter";
    else if (!my_str_isalpha(args[1]) && !my_str_isnum(args[1]))
      error = "Variable name must contain alphanumeric characters";
    else
	sh->env = set_env(args[1], args[2] ? args[2] : "", sh->env);
  else
    error = "Too many arguments";
  if (error)
      my_printf("%Z%s: %s.\n", 2, args[0], error);
  sh->status = error ? 1 : 0;
  free(args);
  return (sh);
}

t_sh	*fn_unsetenv(char *cmd, t_sh *sh)
{
  char	**args;
  int	nb_args;
  int	i;

  i = 0;
  args = my_str_to_wordtab(cmd);
  nb_args = count_args(&args[1]);
  if (nb_args >= 1)
    {
      sh->status = 0;
      while (args[++i])
	sh->env = del_env(args[i], sh->env);
    }
  else
    {
      sh->status = 1;
      my_printf("%Z%s: Too few arguments.\n", 2, args[0]);
    }
  free(args);
  return (sh);
}

t_sh	*fn_env(char *cmd, t_sh *sh)
{
  t_env	*env;

  sh->status = 0;
  env = sh->env;
  while (env)
    {
      my_printf("%s=%s\n", env->name, env->value);
      env = env->next;
    }
  return (sh);
}

t_sh	*fn_exit(char *cmd, t_sh *sh)
{
  char	**args;
  int	nb_args;
  int	code;
  int	check;

  args = my_str_to_wordtab(cmd);
  nb_args = count_args(&args[1]);
  check = (nb_args == 0 || (nb_args == 1 && my_str_isnum(args[1]))) ? 1 : 0;
  code = check && nb_args == 1 ? my_getnbr(args[1]) : 0;
  if (!check)
    my_printf("%Z%s: Expression Syntax.\n", 2, args[0]);
  else
    my_printf("exit\n");
  free(args);
  if (check)
    exit(code);
  return (sh);
}
