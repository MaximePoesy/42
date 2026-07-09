/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:40:50 by staverni          #+#    #+#             */
/*   Updated: 2025/05/14 20:43:44 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_last_dir(void)
{
	int		i;
	char	*cwd;
	char	*last_dir;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (cwd);
	i = ft_strlen(cwd);
	while (i >= 0)
	{
		if (cwd[i] == '/')
		{
			last_dir = ft_strdup(&cwd[i + 1]);
			free(cwd);
			return (last_dir);
		}
		i--;
	}
	return (cwd);
}

static char	*get_host(void)
{
	static char	hostname[256] = {0};
	int			fd;
	ssize_t		bytes_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes_read = read(fd, hostname, sizeof(hostname) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (NULL);
	hostname[bytes_read - 1] = '\0';
	return (hostname);
}

void	concat_prompt(char *prompt_str, char *user, char *host, char *cwd)
{
	size_t	tot_len;

	tot_len = ft_strlen(user) + ft_strlen(host) + ft_strlen(cwd) + 128;
	ft_strlcpy(prompt_str, BLUE, tot_len + 1);
	if (!user || user[0] == '\0')
		ft_strlcat(prompt_str, "unknown", tot_len + 1);
	else
		ft_strlcat(prompt_str, user, tot_len + 1);
	ft_strlcat(prompt_str, "@", tot_len + 1);
	if (!host || host[0] == '\0')
		ft_strlcat(prompt_str, "unknown", tot_len + 1);
	else
		ft_strlcat(prompt_str, host, tot_len + 1);
	ft_strlcat(prompt_str, "\n" RESET "../", tot_len + 1);
	if (!cwd || cwd[0] == '\0')
		ft_strlcat(prompt_str, "unknown", tot_len + 1);
	else
		ft_strlcat(prompt_str, cwd, tot_len + 1);
	ft_strlcat(prompt_str, " ➜ ", tot_len + 1);
}

static char	*make_prompt(t_list *env)
{
	char	*cwd;
	char	*user;
	char	*host;
	char	*prompt_str;
	size_t	tot_len;

	cwd = get_last_dir();
	user = ft_getenv("USER", env);
	host = get_host();
	tot_len = ft_strlen(user) + ft_strlen(host) + ft_strlen(cwd) + 128;
	prompt_str = ft_calloc(tot_len + 1, sizeof(char));
	if (!prompt_str)
		return (free(cwd), free(user), free(host), NULL);
	concat_prompt(prompt_str, user, host, cwd);
	if (user)
		free(user);
	if (cwd)
		free(cwd);
	return (prompt_str);
}

char	*read_input(t_list *env)
{
	char	*input;
	char	*prompt;
	char	*trimmed;

	prompt = make_prompt(env);
	input = readline(prompt);
	free(prompt);
	trimmed = NULL;
	if (input)
	{
		if (input[0] != '\0')
			add_history(input);
		trimmed = ft_strtrim(input, " \t");
		free(input);
		if (!trimmed)
			return (NULL);
	}
	return (trimmed);
}
