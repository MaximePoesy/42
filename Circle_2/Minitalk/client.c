/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:10:49 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/28 12:10:52 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t pid, char bit)
{
	if (bit)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	usleep(300);
}

static void	send_bits(pid_t pid, unsigned long value, int nbits)
{
	int	i;

	i = nbits - 1;
	while (i >= 0)
	{
		send_signal(pid, (value >> i) & 1);
		i--;
	}
}

void	send_message(pid_t pid, const char *message)
{
	size_t	msg_length;

	msg_length = ft_strlen(message) + 1;
	send_bits(pid, msg_length, 32);
	while (*message)
	{
		send_bits(pid, (unsigned long)*message, 8);
		message++;
	}
	send_bits(pid, 0, 8);
}

void	receive_message(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)info;
	(void)context;
	ft_printf("Message received\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	pid_t				pid;
	char				*pid_str;

	act.sa_sigaction = receive_message;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid_str = ft_itoa(ft_atoi(argv[1]));
	if (!pid_str || ft_strcmp(argv[1], pid_str) != 0)
	{
		free(pid_str);
		ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	free(pid_str);
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	return (0);
}
