/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:00:13 by mpoesy            #+#    #+#             */
/*   Updated: 2025/03/19 10:01:21 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

// Define struct to represent stack datatype
typedef struct s_stack
{
	int		*p_array;
	int		top;
	int		len;
	char	stack_name;
}	t_stack;

#endif /* STRUCT_H */
