/*
** mysh.h for mysh in /home/proqui_g/rendu/PSU_2015_minishell1
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Mon Nov 30 09:36:10 2015 Guillaume PROQUIN
** Last update Mon Dec 21 20:12:01 2015 Guillaume PROQUIN
*/

#ifndef		__MY_SH__
# define	__MY_SH__

# include	<sys/stat.h>
# include	<sys/types.h>
# include	<sys/wait.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdarg.h>
# include	<signal.h>
# include	<fcntl.h>
# include	"get_next_line.h"
# include	"my.h"
# include	"my_printf.h"

# define	IS_MAJ(c)	((c) >= 'A' && (c) <= 'Z')
# define	IS_MIN(c)	((c) >= 'a' && (c) <= 'z')
# define	IS_NUM(c)	((c) >= '0' && (c) <= '9')
# define	IS_ALPHANUM(c)	(IS_MAJ(c) || IS_MIN(c) || IS_NUM(c))

# ifndef	BUFFER_SIZE
#  define	BUFFER_SIZE 4
# endif

# define	END_DEL		";"
# define	PIPE_DEL	"|"
# define	RDIR_DEL	">"
# define	LDIR_DEL	"<"
# define	DRDIR_DEL	">>"
# define	DLDIR_DEL	"<<"

typedef struct	s_builtin	t_builtin;
typedef struct	s_env		t_env;
typedef struct	s_param		t_param;
typedef struct	s_sh		t_sh;

typedef struct	s_builtin
{
  char		*name;
  t_sh		*(*f)(char *cmd, t_sh *sh);
}		t_builtin;

typedef struct	s_env
{
  char		*name;
  char		*value;
  t_env		*prev;
  t_env		*next;
}		t_env;

typedef struct	s_sh
{
  int		status;
  t_env		*env;
  char		*pwd;
  char		*old_pwd;

}		t_sh;

typedef struct	s_exec
{
  char		*del;
  void		(*f)(char **av, t_sh *sh, int filefd);
}		t_exec;

t_sh		*fn_cd(char *cmd, t_sh *sh);
t_sh		*fn_setenv(char *cmd, t_sh *sh);
t_sh		*fn_unsetenv(char *cmd, t_sh *sh);
t_sh		*fn_env(char *cmd, t_sh *sh);
t_sh		*fn_exit(char *cmd, t_sh *sh);

int		is_path(char *name);
int		is_valid_path(char *path);
char		*get_path(t_env *env);
char		*get_cmd_path(char *name, t_env *env);

void		check_signal(int pid, t_sh *sh);
void		exec_cmd(char *params, t_sh *sh, int fork);

t_env		*set_var(char *name, char *value);
t_env		*add_env(t_env *var, t_env *env);
t_env		*del_env(char *name, t_env *env);
t_env		*set_env(char *name, char *value, t_env *env);
char		*get_env(char *name, t_env *env);

int		count_args(char **args);
char		*mem_alloc(int size);
void		check_error(char *c, char *file, t_sh *sh);
char		**env_to_tab(t_env *env);
t_env		*env_from_tab(char **ae);

void		call_cmd(char *cmd, t_sh *sh, int fork);
void		prompt();
void		stop_sig();
void		set_path(char *path, t_sh *sh);

int		is_delimiter(char c, char *dels);
int		count_cmds(char *line, char *dels);
char		**get_cmds(char *str, char *dels);
int		parse_input(char *cmd, t_sh *sh);

void		kill_child();
pid_t		check_fork();
void		pipe_child(int pipefd[2], int fd, char **av, t_sh *sh);
void		fn_pipe(char **av, t_sh *sh, int filefd);

void		fn_rdir(char **av, t_sh *sh, int filefd);

void		sig_prompt();
int		find_fn(char *cmd, char *del);
int		check_exec(char *cmd, t_exec *exec);
void		select_exec(char *cmd, t_sh *sh);

#endif
