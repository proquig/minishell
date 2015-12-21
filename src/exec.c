/*
** exec.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Dec 15 23:20:28 2015 Guillaume PROQUIN
** Last update Mon Dec 21 18:11:16 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void		sig_prompt()
{
  my_printf("\n");
}

void		select_exec(char *cmd, t_sh *sh)
{
  char		**cmds;
  int		i;
  char		**args;
  t_exec	exec[] = {
    {RDIR_DEL, &fn_rdir},
    {PIPE_DEL, &fn_pipe},
    {NULL, NULL}
  };

  i = -1;
  signal(SIGINT, sig_prompt);
  while (exec[++i].del && count_cmds(cmd, exec[i].del) <= 1);
  if (exec[i].del)
    {
      args = get_cmds(cmd, exec[i].del);
      exec[i].f(args, sh, 0);
      free(args);
    }
  else
    call_cmd(cmd, sh, 1);
  signal(SIGINT, stop_sig);
}
