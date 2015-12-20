/*
** mysh.c for mysh in /home/proqui_g/PSU_2015_minishell1
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Nov 24 08:50:07 2015 Guillaume PROQUIN
** Last update Sun Dec 20 18:20:30 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void		call_cmd(char *cmd, t_sh *sh, int fork)
{
  int		i;
  char		**args;
  t_builtin	builtins[] = {
    {"cd", &fn_cd},
    {"setenv", &fn_setenv},
    {"unsetenv", &fn_unsetenv},
    {"env", &fn_env},
    {"exit", &fn_exit},
    {NULL, NULL}
  };

  args = my_str_to_wordtab(cmd);
  if (args[0])
    {
      i = -1;
      while (builtins[++i].name && my_strcmp(args[0], builtins[i].name));
      if (builtins[i].name)
	sh = builtins[i].f(cmd, sh);
      else
	exec_cmd(cmd, sh, fork);
      free(args);
    }
}

void		prompt()
{
  my_printf("$> ");
}

void		stop_sig()
{
  my_printf("\n");
  prompt();
}

void		set_path(char *path, t_sh *sh)
{
  if (path)
    {
      sh->status = 0;
      sh->old_pwd = sh->pwd;
      sh->pwd = path;
      sh->env = set_env("PWD", path, sh->env);
    }
}

int		main(int ac, char **av, char **ae)
{
  char		*cmd;
  t_env		*env;
  t_sh		sh;

  env = env_from_tab(ae);
  sh = (t_sh) {0, env, NULL, NULL};
  sh.pwd = get_env("PWD", env) ? get_env("PWD", env) : ".";
  sh.old_pwd = sh.pwd;
  signal(SIGINT, stop_sig);
  prompt();
  while ((cmd = get_next_line(0)))
    {
      if (cmd[0])
	parse_input(cmd, &sh);
      prompt();
    }
  my_printf("exit\n");
  return (sh.status);
}
