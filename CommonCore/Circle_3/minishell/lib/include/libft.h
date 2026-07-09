/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:23:56 by staverni          #+#    #+#             */
/*   Updated: 2025/05/17 15:32:58 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/******************************** INCLUDES ************************************/

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/********************************* DEFINES ************************************/

# define HEX_SET "0123456789abcdef"
# define HEX_SET_UPPER "0123456789ABCDEF"

/******************************** STRUCTURES **********************************/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*********************************** BASE *************************************/

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_iswhitespace(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strcspn(const char *s, const char *charset);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strpbrk(const char *s, const char *accept);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strspn(const char *s, const char *accept);
void	ft_strswap(char **a, char **b);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_swap(char *a, char *b);
int		ft_tolower(int c);
int		ft_toupper(int c);

/********************************** Lists *************************************/

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstfind(t_list *lst, void *data_ref,
			int (*cmp)(const void *, const void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstpop(t_list **lst, void *ref, int (*cmp)(void *, void *),
			void (*del)(void *));
int		ft_lstsize(t_list *lst);

/********************************** PRINTF ************************************/

int		ft_printf(const char *str, ...);
int		case_c(int c);
int		case_di(int n);
int		case_p(const void *p);
int		case_s(char *s);
int		case_u(const unsigned int n);
int		case_x(unsigned int n, const char c);

#endif
