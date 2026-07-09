/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:01:10 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 10:01:11 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

# include <stdbool.h>
# include "../struct.h"
# include "../gets/gets.h"

bool	is_ordered(const t_stack *stack);
bool	is_sorted(const t_stack *stack);

#endif
