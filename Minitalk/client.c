/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:15:17 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/21 11:07:44 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	send_signal(pid_t pid, char bit)
{
	if (bit)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	usleep(200);
}

void	send_message(pid_t pid, const char *message)
{
	int	i;
	int	j;

	while (*message)
	{
		j = 7;
		while (j >= 0)
		{
			send_signal(pid, (*message >> j) & 1);
			j--;
		}
		message++;
	}
	i = 0;
	while (i < 8)
	{
		send_signal(pid, 0);
		i++;
	}
	pause();
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
