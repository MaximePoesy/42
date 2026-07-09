/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:13 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/15 11:51:55 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(const char *key, t_list **env)
{
	t_list	*prev;
	t_list	*current;

	prev = NULL;
	current = *env;
	if (!current)
		return ;
	while (current)
	{
		if (compare_env_name(current->content, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->content);
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_execcmd *cmd, t_list **env)
{
	int	i;

	if (!cmd || !env)
		return (1);
	if (!cmd->argv[1])
		return (0);
	i = 1;
	while (cmd->argv[i])
	{
		remove_env_var(cmd->argv[i], env);
		i++;
	}
	return (0);
}
