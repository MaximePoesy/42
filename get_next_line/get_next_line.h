/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:41:32 by gemartin          #+#    #+#             */
/*   Updated: 2022/03/02 12:48:07 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*free_and_nullify(char **str);
#endif
