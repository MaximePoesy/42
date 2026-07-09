/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:32:43 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/28 12:23:21 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_state
{
	unsigned int	length;
	int				length_bits;
	int				msg_length;
	char			*message;
	unsigned char	current_char;
	int				char_bits;
	int				msg_index;
	int				receiving_length;
}					t_state;

void				init_state(t_state *st);
#endif
