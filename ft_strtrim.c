/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tf_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:38:58 by mpoesy            #+#    #+#             */
/*   Updated: 2025/06/18 16:39:38 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
		i++;
	return i;
}

size_t	find_start(const char *s1, char const *set)
{
	int	mybool;
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	start = 0;
	while (s1[i])
	{
		mybool = 1;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				mybool = 0;
			j++;
		}
		if (mybool == 1)
			break;
		start++;
		i++;
	}
	return (start);
}

size_t	find_end(const char *s1, const char *set)
{
	size_t	n;
	size_t	j;
	size_t	end;
	int	mybool;

	end = 0;
	n = ft_strlen(s1);
	while (n > 0 && s1[n-1])
	{
		mybool = 1;
		j = 0;
		while (set[j])
                {
                        if (s1[n - 1] == set[j])
                                mybool = 0;
			j++;
                }
                if (mybool == 1)
                        break;
		end++;
		n--;
	}
	return (end);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;
	char	*new_str;

	if (!s1 || !set)
		return NULL;
	len = ft_strlen(s1);
	start = find_start(s1, set);
	if (start == len)
		return "";
	end = find_end(s1, set);
	new_str = malloc(len - start - end);
	i = 0;
	while (i < len - start - end)
	{
		new_str[i] = s1[start + i];
		i++;
	}
	return(new_str);
}

int main()
{
	char *str = "HAHAlolHAHA";
	char *set = "HA";
	char *new_str;
	new_str = ft_strtrim(str, set);
	printf("str : -%s-\n", new_str);
	return 0;
}
