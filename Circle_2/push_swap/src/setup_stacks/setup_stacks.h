/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_stacks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:17 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 10:01:19 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_STACKS_H
# define SETUP_STACKS_H

# include "../struct.h"
# include <stdlib.h>
# include "../mini_strtoi/mini_strtoi.h"
# include "../../libft/libft.h"
# include <stdio.h>

void	free_stacks(t_stack *stack_a, t_stack *stack_b);
void	populate_stack(int argc, char *argv[], t_stack *stack);
int		initialize_stack(t_stack *stack, int len, char stack_name);

#endif /* SETUP_STACKS_H */
