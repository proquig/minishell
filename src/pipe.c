/*
** my_exec2.c for my_exec in /home/proqui_g/rendu/PSU_2015_my_exec2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Dec  8 08:40:49 2015 Guillaume PROQUIN
** Last update Mon Dec 21 20:05:20 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void	kill_child()
{
  exit(0);
}

pid_t	check_fork()
{
  pid_t	pid;

  if ((pid = fork()) == -1)
    {
      my_fprintf(2, "Failed to fork\n");
      exit(2);
    }
  if (pid == 0)
    signal(SIGINT, kill_child);
  return (pid);
}

void	pipe_child(int pipefd[2], int fd, char **av, t_sh *sh)
{
  dup2(fd != -1 ? fd : pipefd[0], 0);
  if (av[1] || fd == -1)
    dup2(pipefd[1], 1);
  close(pipefd[0]);
  call_cmd(av[0], sh, 0);
  exit(0);
}

void    fn_pipe(char **av, t_sh *sh, int filefd)
{
  int   fd;
  pid_t pid;
  int	i;
  int   pipefd[2] = {
    0, 0
  };

  i = -1;
  fd = 0;
  while (av[++i] && av[i + 1])
    {
      pipe(pipefd);
      if ((pid = check_fork()) == 0)
	pipe_child(pipefd, fd, &av[i], sh);
      else
	{
	  close(pipefd[1]);
	  fd = pipefd[0];
	}
    }
  if (filefd)
    pipefd[1] = filefd;
  if ((pid = check_fork()) == 0)
    pipe_child(pipefd, filefd ? -1 : fd, &av[i], sh);
  check_signal(pid, sh);
}
