/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:22:19 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/28 12:23:09 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_state(t_state *st)
{
	st->length = 0;
	st->length_bits = 0;
	st->msg_length = 0;
	st->message = NULL;
	st->current_char = 0;
	st->char_bits = 0;
	st->msg_index = 0;
	st->receiving_length = 1;
}
