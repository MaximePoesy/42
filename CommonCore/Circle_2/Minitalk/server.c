/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:10:56 by mpoesy            #+#    #+#             */
/*   Updated: 2025/02/28 12:30:27 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_state	*get_state(void)
{
	static t_state	state;
	static int		initialized = 0;

	if (!initialized)
	{
		init_state(&state);
		initialized = 1;
	}
	return (&state);
}

static void	update_length(t_state *st, int signo)
{
	if (signo == SIGUSR2)
		st->length = st->length << 1 | 1;
	else
		st->length = st->length << 1 | 0;
	st->length_bits++;
	if (st->length_bits == 32)
	{
		st->msg_length = st->length;
		st->message = malloc(st->msg_length + 1);
		if (!st->message)
		{
			ft_printf("Memory allocation error\n");
			exit(1);
		}
		st->receiving_length = 0;
	}
}

static void	update_char(t_state *st, int signo, siginfo_t *info)
{
	if (signo == SIGUSR2)
		st->current_char = st->current_char << 1 | 1;
	else
		st->current_char = st->current_char << 1 | 0;
	st->char_bits++;
	if (st->char_bits == 8)
	{
		st->message[st->msg_index++] = st->current_char;
		if (st->current_char == '\0' && st->msg_index == st->msg_length)
		{
			ft_printf("%s", st->message);
			kill(info->si_pid, SIGUSR1);
			free(st->message);
			init_state(st);
		}
		st->current_char = 0;
		st->char_bits = 0;
	}
}

static void	handle_signal(int signo, siginfo_t *info, void *context)
{
	t_state	*st;

	st = get_state();
	(void)context;
	if (st->receiving_length)
		update_length(st, signo);
	else
		update_char(st, signo, info);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handle_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act,
			NULL) == -1)
	{
		ft_printf("Error setting signal handlers\n");
		return (1);
	}
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
