/*
** my_exec2.c for my_exec in /home/proqui_g/rendu/PSU_2015_my_exec2
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Dec  8 08:40:49 2015 Guillaume PROQUIN
** Last update Mon Dec 21 18:14:46 2015 Guillaume PROQUIN
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

/*
void    fn_rdir(char **av, t_sh *sh)
{
  int   pipefd[2];
  int   fd;
  pid_t pid;
  int	i;

  i = -1;
  fd = 0;
  while (av[++i] && av[i + 2])
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
  pipefd[1] = open(av[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0664);
  if ((pid = check_fork()) == 0)
    {
      pipe_child(pipefd, -1, &av[i], sh);
      //dup2(pipefd[0], 0);
      //dup2(filefd, 1);
      //close(pipefd[0]);
      //call_cmd(av[i], sh, 0);
      //exit(0);
    }
  check_signal(pid, sh);
}
*/

void    fn_pipe(char **av, t_sh *sh, int filefd)
{
  int   pipefd[2];
  int   fd;
  pid_t pid;
  int	i;

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

void	fn_rdir(char **av, t_sh *sh, int filefd)
{
  char	**args;
  char	**name;

  name = get_cmds(av[1], " \t");
  filefd = open(name[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
  args = get_cmds(av[0], PIPE_DEL);
  fn_pipe(args, sh, filefd);
}
