/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:52:07 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 15:45:31 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_error_null(char *message)
{
	if (message)
	{
		write(2, "minishell: ", 11);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	return (NULL);
}

void	*token_syntax_error(char *token, size_t len)
{
	if (token)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, token, len);
		write(2, "'\n", 2);
	}
	return (NULL);
}

void	*exec_error(char *exec)
{
	if (exec)
	{
		write(2, "minishell: ", 11);
		if (exec)
			write(2, exec, ft_strlen(exec));
		else
			write(2, "unknown", 7);
		write(2, ": command not found\n", 20);
	}
	return (0);
}

int	access_error(char *file, int mode)
{
	if (file)
	{
		write(2, "minishell: ", 11);
		if (file)
			write(2, file, ft_strlen(file));
		else
			write(2, "unknown", 7);
		if (mode == F_OK)
			write(2, ": No such file or directory\n", 28);
		else if (mode == W_OK || mode == R_OK)
			write(2, ": Permission denied\n", 20);
		else
			write(2, ": Access error\n", 15);
	}
	return (0);
}
