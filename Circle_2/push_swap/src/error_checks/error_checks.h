/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:07 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 10:01:08 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECKS_H
# define ERROR_CHECKS_H

# include <stdlib.h>
# include <unistd.h>
# include "../mini_strtoi/mini_strtoi.h"
# include "../setup_stacks/setup_stacks.h"

void	display_err_exit(void);
int		ft_strcmp(const char *s1, const char *s2);
void	check_for_int_and_overflow(int argc, char *argv[]);
void	exit_if_duplicate(t_stack *stack_a, t_stack *stack_b);

#endif /* ERROR_CHECKS_H */
