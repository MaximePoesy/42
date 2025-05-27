/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:11:25 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/27 17:54:15 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_timestamp(struct timeval *start_time)
{
	gettimeofday(start_time, NULL);
}

long	timestamp(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000L + (now.tv_usec - start.tv_usec)
		/ 1000L);
}
