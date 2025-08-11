/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:08 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 10:01:09 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETS_H
# define GETS_H

# include "../struct.h"

int		get_minimum(const t_stack *stack);
int		get_maximum(const t_stack *stack);
int		get_index(const t_stack *stack, int element);

#endif /* GETS_H */
