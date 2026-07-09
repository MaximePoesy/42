/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:58:06 by mpoesy            #+#    #+#             */
/*   Updated: 2025/05/14 19:15:53 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(void *content)
{
	printf("%s\n", (char *)content);
}

int	builtin_env(t_list *env)
{
	ft_lstiter(env, print_env);
	return (0);
}
