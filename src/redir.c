/*
** redir.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Dec 21 20:04:02 2015 Guillaume PROQUIN
** Last update Mon Dec 21 20:58:52 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void	fn_rdir(char **av, t_sh *sh, int filefd)
{
  char  **args;
  char  **name;

  name = get_cmds(av[1], " \t");
  if (filefd)
    filefd = open(name[0], O_RDWR | O_CREAT | O_APPEND, 0664);
  else
    filefd = open(name[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
  if (filefd == -1)
    check_error("cd", name[0], sh);
  else
    {
      args = get_cmds(av[0], PIPE_DEL);
      fn_pipe(args, sh, filefd);
      close(filefd);
    }
}

void	fn_ldir(char **av, t_sh *sh, int filefd)
{
  int	pid;
  char	**name;

  if ((pid = check_fork()) == 0)
    {
      name = get_cmds(av[1], " \t");
      if ((filefd = open(name[0], O_RDONLY, 0664)) == -1)
	check_error("cd", name[0], sh);
      else
	{
	  dup2(filefd, 0);
	  close(filefd);
	  call_cmd(av[0], sh, 0);
	}
      exit(0);
    }
  check_signal(pid, sh);
}
