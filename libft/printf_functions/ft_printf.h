/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 09:36:40 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/29 15:30:05 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft.h"
# include <stdio.h>

struct	s_print{
	int cap;
	int	plus;
	int minus;
	int	pound;
	int zero;
	int	l_1;
	int	l_2;
	int	h_1;
	int	h_2;
	int	j;
	int	z;
	int	loc;
	int	size;
	int	perc;
	int	just_size;
	int	before_size;
	int	before_len;
	int	after_size;
	int	after_len;
	int precision;
	int	space;
};

struct	s_format{
	int	s;
	int	s2;
	int	p;
	int	d;
	int	d2;
	int	i;
	int	o;
	int	o2;
	int	u;
	int	u2;
	int	x;
	int	x2;
	int	c;
	int	c2;
	int	len;
};
void	print_zero(struct s_format *let, struct s_print *flags);
int		parse_flag(const char *format, int i, struct s_print *flags);
int		parse_size(const char *format, int i, struct s_print *flags);
int		parse_form2(const char *format, int i, struct s_format *let);
int		parse_form(const char *format, int i, struct s_format *let);
int		parse_just(const char *format, int i, struct s_format *let,
					struct s_print *flags);
void	print_just(struct s_format *let, struct s_print *flags,
		intmax_t num, char *str);
void	get_format_d(struct s_format *let, struct s_print *flags, va_list vl);
void	get_format_d2(struct s_format *let, struct s_print *flags, va_list vl);
void	get_format_c(struct s_print *flags, struct s_format *let, va_list vl);
void	get_format_s(struct s_print *flags, struct s_format *let, va_list vl);
void	get_format_x(struct s_format *let, struct s_print *flags, va_list vl);
void	get_format_x2(struct s_format *let, struct s_print *flags, va_list vl);
void	get_format_p(struct s_format *let, struct s_print *flags, va_list vl);
void	get_format_u(struct s_format *let, struct s_print *flags, va_list vl);
void	get_format_i(struct s_format *let, struct s_print *flags, va_list vl);
void	print_plus(struct s_format *let, struct s_print *flags, int num);
void	print_flags(struct s_format *let, struct s_print *flags, long num,
		char *str);
int		get_size(int i, const char *format, struct s_format *let,
				struct s_print *flags);
char	*ft_itoa(int n);
char	*ft_ltoa_base(long long n, int base);
char	*ft_ultoa_base(unsigned long long n, int base);
int		get_num_len_i(int num);
void	ft_putlong(struct s_print *flags, long long n);
void	ft_putulong(struct s_print *flags, unsigned long long n);
char	*ft_strrev(char *str);
char	*d_to_o(unsigned long long num);
void	get_format_o(struct s_format *let, struct s_print *flags, va_list vl);
void	ft_putnbr_pr(int n, struct s_print *flags);
void	define_values(struct s_print *flags, struct s_format *let);
void	define_values2(struct s_print *flags);
void	print_flags_back(struct s_format *let, struct s_print *flags,
						long num, char *str);
void	print_minus(struct s_format *let, struct s_print *flags);
int		get_num_len(long num);
int		get_num_len_i(int num);
int		get_percent(const char *format, int i);
int		get_size2(const char *format, int i, struct s_print *flags);
void	ft_putstr_prec(char *str, struct s_print *flags);
void	ft_putwstr_prec(wchar_t *str, struct s_print *flags);
void	print_pound(struct s_format *let, struct s_print *flags, char *str);
void	print_space(struct s_format *let, struct s_print *flags, long num);
void	get_xo_let(struct s_format *let, char *str, struct s_print *flags);
int		check_form(const char *format, int i);
int		get_size_zer(const char *format, int i, struct s_print *flags);
void	many_formats(struct s_print *flags, struct s_format *let, va_list vl);
int		get_parse_flag_i(const char *format, int i, struct s_print *flags,
		struct s_format *let);
int		get_parse_size_i(const char *format, int i, struct s_print *flags);
int		get_parse_form_i(struct s_print *flags, struct s_format *let,
		va_list vl, int i);
int		get_space_i(const char *format, int i, struct s_print *flags);
int		get_last_i(const char *format, int i, struct s_print *flags);
int		get_print_just_i(struct s_format *let, struct s_print *flags,
		intmax_t num, char *str);
void	print_space_min(int i, int zerlen, intmax_t num, struct s_print *flags);
void	print_just_zer(int j, int zerlen, struct s_print *flags);
char	*ft_ltoa(long long n);
void	get_last_d(struct s_format *let, struct s_print *flags, va_list vl);
int		ft_printf(const char *format, ...);

#endif
