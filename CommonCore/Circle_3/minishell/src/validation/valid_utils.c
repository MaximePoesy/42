/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:53:41 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 15:53:43 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	test_perms(char *file_path)
{
	if (access(file_path, R_OK) == 0)
		printf("Read permission: Yes\n");
	else
		printf("Read permission: No\n");
	if (access(file_path, W_OK) == 0)
		printf("Write permission: Yes\n");
	else
		printf("Write permission: No\n");
	if (access(file_path, X_OK) == 0)
		printf("Execute permission: Yes\n");
	else
		printf("Execute permission: No\n");
	if (access(file_path, F_OK) == 0)
		printf("File exists: Yes\n");
	else
		printf("File exists: No\n");
}
