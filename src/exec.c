/*
** exec.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Dec 15 23:20:28 2015 Guillaume PROQUIN
** Last update Sun Dec 20 18:17:11 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void		sig_prompt()
{
  my_printf("\n");
}

void		select_exec(char *cmd, t_sh *sh)
{
  char		**args;
  char		**cmds;
  char		*del;
  int		i;

  i = -1;
  cmds = get_cmds(cmd, PIPE_DEL);
  signal(SIGINT, sig_prompt);
  if (cmds[1])
    fn_pipe(cmds, sh);
  else
    call_cmd(cmd, sh, 1);
  signal(SIGINT, stop_sig);
  free(cmds);
}
