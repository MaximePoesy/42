/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:43:42 by staverni          #+#    #+#             */
/*   Updated: 2025/05/04 15:23:09 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_is_valid(char *path)
{
	struct stat	sb;

	if (!path || !*path)
		return (0);
	if (stat(path, &sb) != 0)
		return (0);
	if ((sb.st_mode & S_IFMT) == S_IFREG && access(path, X_OK) == 0)
		return (1);
	return (0);
}

static char	*make_cmd_path(char *cmd_name, char **paths)
{
	char	*full_path;
	size_t	path_len;
	int		i;

	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]) + ft_strlen(cmd_name) + 2;
		full_path = malloc(sizeof(char) * path_len);
		if (!full_path)
			return (print_error_null("malloc"));
		ft_strlcpy(full_path, paths[i], path_len);
		ft_strlcat(full_path, "/", path_len);
		ft_strlcat(full_path, cmd_name, path_len);
		if (path_is_valid(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*resolve_cmd_path(char *cmd_name, t_list *env)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (!cmd_name || ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	path_env = ft_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		free(path_env);
		return (print_error_null("malloc"));
	}
	full_path = make_cmd_path(cmd_name, paths);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	free(path_env);
	return (full_path);
}
