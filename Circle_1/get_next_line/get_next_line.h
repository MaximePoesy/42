/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoesy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:21:16 by mpoesy            #+#    #+#             */
/*   Updated: 2025/01/06 09:22:08 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define FD_MAX 1024
# include <fcntl.h>
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
