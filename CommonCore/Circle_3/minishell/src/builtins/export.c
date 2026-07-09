/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:09 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/17 15:32:06 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sorted_list(t_list *env)
{
	char	**sorted;
	int		i;
	int		j;
	int		len;

	sorted = list_to_envp(env);
	if (!sorted)
		return (NULL);
	len = ft_lstsize(env);
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				ft_strswap(&sorted[i], &sorted[j]);
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

static void	export_no_args(t_list **env)
{
	char	**sorted;
	int		i;

	sorted = sorted_list(*env);
	if (!sorted)
		return ;
	i = -1;
	while (sorted[++i])
		printf("export %s\n", sorted[i]);
	free(sorted);
}

static int	assign_key_value(char *arg, char **key, char **value)
{
	*key = env_name(arg);
	if (!*key)
		return (1);
	*value = env_value(arg);
	if (!value)
	{
		free(*key);
		*key = NULL;
		return (1);
	}
	return (0);
}

void	handle_export_arg(char *arg, t_list **env)
{
	char	*key;
	char	*value;
	char	*new_content;
	t_list	*found;

	if (assign_key_value(arg, &key, &value))
		return ;
	new_content = build_env_string(key, value);
	if (!new_content)
		return ;
	found = ft_lstfind(*env, key, compare_env_name);
	if (found)
	{
		free(found->content);
		found->content = new_content;
	}
	else
		ft_lstadd_back(env, ft_lstnew(new_content));
	free(key);
	free(value);
}

int	builtin_export(t_execcmd *cmd, t_list **env)
{
	int		i;

	i = 1;
	if (cmd->argc == 1)
		export_no_args(env);
	while (cmd->argv[i])
	{
		if (!ft_strchr(cmd->argv[i], '='))
		{
			i++;
			continue ;
		}
		handle_export_arg(cmd->argv[i], env);
		i++;
	}
	return (0);
}
