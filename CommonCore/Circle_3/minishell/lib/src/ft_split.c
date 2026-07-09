/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:43 by staverni          #+#    #+#             */
/*   Updated: 2024/10/25 14:42:17 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	wc(const char *s, char c)
{
	int	wc;
	int	in_word;

	if (!s)
		return (0);
	wc = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			wc++;
		}
		s++;
	}
	return (wc);
}

static char	**mem_alloc(const char *s, char c, int wcount)
{
	int		i;
	int		wlength;
	char	**splitter;

	splitter = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!splitter)
		return (NULL);
	i = 0;
	while (i < wcount)
	{
		while (*s == c)
			s++;
		wlength = len(s, c);
		splitter[i] = (char *)malloc(sizeof(char) * (wlength + 1));
		if (!splitter[i])
		{
			while (i > 0)
				free(splitter[--i]);
			free(splitter);
			return (NULL);
		}
		i++;
		s += wlength;
	}
	return (splitter);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		wl;
	int		wcount;
	char	**splitter;

	wcount = wc(s, c);
	splitter = mem_alloc(s, c, wcount);
	if (!splitter)
		return (NULL);
	i = 0;
	while (i < wcount)
	{
		while (*s == c)
			s++;
		wl = len (s, c);
		j = -1;
		while (++j < wl)
			splitter[i][j] = *s++;
		splitter[i][wl] = '\0';
		i++;
	}
	splitter[wcount] = NULL;
	return (splitter);
}
