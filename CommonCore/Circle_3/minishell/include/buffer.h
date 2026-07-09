/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:44:22 by staverni          #+#    #+#             */
/*   Updated: 2025/05/15 20:45:17 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <stdlib.h>

typedef struct s_buffer
{
	char	*data;
	size_t	len;
	size_t	capacity;
}			t_buffer;

/********************************* BUFFER *************************************/

int			buffer_init(t_buffer *buf, size_t initial_capacity);
int			buffer_append(t_buffer *buf, const char *str, size_t len_to_append);
char		*buffer_finalize(t_buffer *buf);
void		buffer_free_data(t_buffer *buf);
int			assign_buffer(t_buffer *buf, char **str);

#endif
