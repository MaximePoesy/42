/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:53:00 by gemartin          #+#    #+#             */
/*   Updated: 2024/12/17 16:12:56 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define FD_MAX 1024
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
