/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:03 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/15 11:52:39 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	suppress_newline(t_execcmd *cmd, int *i)
{
	int	j;
	int	sup_n;

	sup_n = 0;
	while (cmd->argv[*i] && cmd->argv[*i][0] == '-')
	{
		j = 1;
		if (cmd->argv[*i][j] == 'n')
		{
			while (cmd->argv[*i][j] == 'n')
				j++;
			if (cmd->argv[*i][j] == '\0')
				sup_n = 1;
		}
		else
			break ;
		++(*i);
	}
	return (sup_n);
}

int	builtin_echo(t_execcmd *cmd)
{
	int	i;
	int	sup_n;

	i = 1;
	sup_n = suppress_newline(cmd, &i);
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (!sup_n)
		printf("\n");
	return (0);
}
