/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:33 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/21 09:19:02 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	receive_bit(int signo, siginfo_t *info, void *context)
{
	static char	received_data = 0;
	static int	bit_count = 0;

	(void)context;
	if (bit_count < 8)
	{
		received_data = (received_data << 1) | (signo == SIGUSR2);
		bit_count++;
	}
	if (bit_count == 8)
	{
		write(1, &received_data, 1);
		if (received_data == '\0')
			kill(info->si_pid, SIGUSR1);
		received_data = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = receive_bit;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
