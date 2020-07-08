/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:01:16 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/04 23:24:46 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define MAX_FD 1025
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			**ft_split(char const *s, char c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_putnbr_base(int nbr, char *base);
char			*ft_itoa_base(int n, char *base);
char			*ft_itoa_base_long(long int n, char *base);
int				ft_isinstring(int c, char *str);
int				get_next_line(int fd, char **line);
int				gnl_strchr(char **rest, char **line);
int				gnl_read_file(char *temp, char **rest, char **line, int fd);
int				gnl_strlen(const char *s);
char			*gnl_strdup(const char *s1);
char			*gnl_strjoin(char *s1, char *s2);
int				gnl_free_mem(char *s1, char *s2, int value);
int				ft_isspace(int c);
int				ft_strcmp(const char *s1, const char *s2);
t_list			*ft_create_elem(void *content);
void			ft_list_push_front(t_list **begin_list, void *content);
int				ft_list_size(t_list *begin_list);
t_list			*ft_list_last(t_list *begin_list);
void			ft_list_push_back(t_list **begin_list, void *content);
t_list			*ft_list_push_strs(int size, char **strs);
void			ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
void			ft_list_reverse(t_list **begin_list);
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
void			ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
					void *content_ref, int (*cmp)());
t_list			*ft_list_find(t_list *begin_list, void *content_ref,
					int (*cmp)());
void			ft_list_remove_if(t_list **begin_list, void *content_ref,
					int (*cmp)(), void (*free_fct)(void *));
void			ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void			ft_list_sort(t_list **begin_list, int (*cmp)());
void			ft_list_reverse_fun(t_list *begin_list);
void			ft_sorted_list_insert(t_list **begin_list,
					void *content, int (*cmp)());
void			ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2,
					int (*cmp)());

#endif
