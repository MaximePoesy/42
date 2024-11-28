/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:23:12 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/28 17:23:09 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/* '-' = 000001
 * '0' = 000010
 * '.' = 000100
 * '#' = 001000
 * '+' = 010000
 * ' ' = 100000
 */

# define FLAG_MINUS 0b000001
# define FLAG_ZERO 0b000010
# define FLAG_DOT 0b000100
# define FLAG_HASH 0b001000
# define FLAG_PLUS 0b010000
# define FLAG_SPACE 0b100000

typedef struct s_format
{
	int		flags;
	int		iswidthsetup;
	int		width;
	size_t	precision;
}			t_format;

int			ft_printf(const char *str, ...);
int			print_c(int c, t_format *format);
int			print_s(char *str, t_format *format);
int			print_p(void *ptr, t_format *format);
int			print_d(int nbr, t_format *format);
int			print_i(int nbr, t_format *format);
int			print_u(unsigned int nbr, t_format *format);
int			print_x(unsigned int nbr, t_format *format);
int			print_cx(unsigned int nbr, t_format *format);
int			print_prc(void);
int			parse_width(const char **str, int *iswidthsetup);
int			parse_precision(const char **str, int *flag);
t_format	parse_format(const char **str);
int			parse_flags(const char **str);
char		*apply_flags(char *str, t_format *format, char specifier);
char		*add_prefix(char *str, char *prefix);
char		*ft_itoa_base(size_t num, int base);
char    *ft_utoa(unsigned int n);
char		*apply_width_and_padding(char *str, t_format *format, char specifier);
int     handle_zero(t_format *format);
char *precision_d(char *str, t_format *format);
char *precision_s(char *str, t_format *format);
char *precision_u(char *str, t_format *format);
char *precision_x(char *str, t_format *format);
char *precision_cx(char *str, t_format *format);

#endif
