/*
** cmd.c for mysh in /home/proqui_g/rendu/PSU_2015_minishell1
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Nov 30 10:54:14 2015 Guillaume PROQUIN
** Last update Fri Dec 18 16:15:51 2015 Guillaume PROQUIN
*/

#include "mysh.h"

void	check_signal(int pid, t_sh *sh)
{
  int	signal;
  int	i;
  char	*msgs[34];

  i = -1;
  while (++i < 34)
    msgs[i] = NULL;
  msgs[SIGQUIT] = "Quit";
  msgs[SIGILL] = "Illegal instruction";
  msgs[SIGABRT] = "Abort";
  msgs[SIGFPE] = "Floating point exception";
  msgs[SIGKILL] = "Killed";
  msgs[SIGBUS] = "Bus error";
  msgs[SIGSEGV] = "Segmentation fault";
  msgs[SIGSYS] = "Bad system call";

  waitpid(pid, &sh->status, 0);
  while (!WIFEXITED(sh->status) && !WIFSIGNALED(sh->status))
    waitpid(pid, &sh->status, 0);
  if (WIFSIGNALED(sh->status))
    {
      signal = WTERMSIG(sh->status);
      if (signal >= 0 && signal < 34)
	my_printf("%s\n", msgs[signal] ? msgs[signal] : "");
    }
}

void	exec_cmd(char *params, t_sh *sh, int fork)
{
  char	**args;
  char	**env;
  char	*path;
  int	child_pid;

  env = NULL;
  args = my_str_to_wordtab(params);
  path = is_path(args[0]) ? args[0] : get_cmd_path(args[0], sh->env);
  if (is_valid_path(path))
    if ((child_pid = fork ? check_fork() : 0) == 0)
      execve(path, &args[0], env = env_to_tab(sh->env));
    else
      check_signal(child_pid, sh);
  else
    check_error(args[0], args[0], sh);
  free(args);
  if (env)
    free(env);
}
