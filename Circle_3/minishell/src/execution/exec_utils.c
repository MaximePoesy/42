/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:31:38 by staverni          #+#    #+#             */
/*   Updated: 2025/05/18 10:42:54 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_in_parent(char *path)
{
	if (!path)
		return (0);
	if (ft_strcmp(path, "cd") == 0)
		return (1);
	if (ft_strcmp(path, "exit") == 0)
		return (1);
	if (ft_strcmp(path, "export") == 0)
		return (1);
	if (ft_strcmp(path, "unset") == 0)
		return (1);
	return (0);
}
