/*
** exec.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Dec 15 23:20:28 2015 Guillaume PROQUIN
** Last update Mon Dec 21 22:38:55 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void		sig_prompt()
{
  my_printf("\n");
}

int		find_fn(char *cmd, char *del)
{
  int		i;
  int		j;

  i = -1;
  j = 0;
  while (cmd[++i])
    {
      if (cmd[i] == del[j])
	{
	  if (!del[++j])
	    return (1);
	}
      else
	j = 0;
    }
  return (0);
}

int		check_exec(char *cmd, t_exec *exec)
{
  char		**args;
  int		check;
  int		i;
  int		j;

  args = get_cmds(cmd, " \t");
  check = 1;
  i = -1;
  j = -1;
  if (!args || !args[0])
    check = 0;
  while (check && args[++i]);
  while (check && exec[++j].del)
    if (args[i - 1][0] == exec[j].del[0] \
	|| args[i - 1][my_strlen(args[i - 1]) - 1] == exec[j].del[0])
      check = 0;
    else if (find_fn(cmd, exec[j].del) && count_cmds(cmd, exec[j].del) < 2)
      check = 0;
  if (!check && exec[j + 1].del)
    my_fprintf(2, "Missing name for redirect.\n");
  if (!check && !exec[j + 1].del)
    my_fprintf(2, "Invalid null command.\n");
  return (check);
}

void		select_exec(char *cmd, t_sh *sh)
{
  int		i;
  char		**args;
  t_exec	exec[] = {
    {DRDIR_DEL, &fn_rdir},
    {DLDIR_DEL, &fn_rdir},
    {RDIR_DEL, &fn_rdir},
    {LDIR_DEL, &fn_ldir},
    {PIPE_DEL, &fn_pipe},
    {NULL, NULL}
  };

  i = -1;
  signal(SIGINT, sig_prompt);
  while (exec[++i].del && !find_fn(cmd, exec[i].del));
  if (count_cmds(cmd, " \t") && check_exec(cmd, exec))
    if (exec[i].del)
      {
	args = get_cmds(cmd, exec[i].del);
	exec[i].f(args, sh, my_strlen(exec[i].del) > 1);
	free(args);
      }
    else
      call_cmd(cmd, sh, 1);
  signal(SIGINT, stop_sig);
}
