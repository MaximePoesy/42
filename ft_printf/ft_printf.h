/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:23:12 by mpoesy            #+#    #+#             */
/*   Updated: 2024/11/05 13:53:16 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define FLAG_MINUS 0b000001
# define FLAG_ZERO 0b000010
# define FLAG_DOT 0b000100
# define FLAG_HASH 0b001000
# define FLAG_PLUS 0b010000
# define FLAG_SPACE 0b100000

typedef struct s_format
{
	int	flags;
	int	width;
	int	precision;
}		t_format;

int		ft_printf(const char *str, ...);
int		print_c(int c);
int		print_s(char *str);
int		print_p(void *ptr);
int		print_d(int nbr);
int		print_i(int nbr);
int		print_u(unsigned int nbr);
int		print_x(unsigned int nbr);
int		print_cx(unsigned int nbr);
int		print_prc(void);

#endif
