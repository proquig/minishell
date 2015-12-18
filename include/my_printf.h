/*
** my_printf.h for my_printf in /home/proqui_g/rendu/PSU_2015_my_printf
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue Nov  3 09:19:53 2015 Guillaume PROQUIN
** Last update Sat Nov 14 15:21:02 2015 Guillaume PROQUIN
*/

#ifndef		__MY_PRINTF__
# define	__MY_PRINTF__

typedef struct	s_print t_print;
typedef struct	s_param t_param;

typedef struct	s_param
{
  int		*i;
  const char	*p;
}		t_param;

typedef struct	s_print
{
  char		c;
  void		(*f)(va_list arg, t_param param);
  t_param	p;
}		t_print;

void		put_text(t_param param, int f, const char *text);
void		print_char(va_list arg, t_param param);
void		print_str(va_list arg, t_param param);
void		print_npr(va_list arg, t_param param);
void		print_buf(va_list arg, t_param param);

int		my_print_nbr_base(t_param param, long int nbr, const char *base);
void		print_int(va_list arg, t_param param);
void		print_uint(va_list arg, t_param param);
void		print_ptr(va_list arg, t_param param);

void		select_print(t_param format, va_list arg);
int		my_printf(const char *format, ...);

#endif
