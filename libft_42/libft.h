/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:37:02 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/16 15:59:28 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_FD 1025
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
t_list			*ft_create_elem(void *content);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isinstring(int c, char *str);
int				ft_isspace(int c);
char			*ft_itoa_base_long(long int n, char *base);
char			*ft_itoa_base(int n, char *base);
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
void			ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
t_list			*ft_list_find(t_list *begin_list, void *content_ref,
					int (*cmp)());
void			ft_list_foreach_if(t_list *begin_list, void (*f)(void *), void
					*content_ref, int (*cmp)());
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
t_list			*ft_list_last(t_list *begin_list);
void			ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void			ft_list_push_back(t_list **begin_list, void *content);
void			ft_list_push_front(t_list **begin_list, void *content);
t_list			*ft_list_push_strs(int size, char **strs);
void			ft_list_remove_if(t_list **begin_list, void *content_ref,
					int (*cmp)(), void (*free_fct)(void *));
void			ft_list_reverse_fun(t_list *begin_list);
void			ft_list_reverse(t_list **begin_list);
int				ft_list_size(t_list *begin_list);
void			ft_list_sort(t_list **begin_list, int (*cmp)());
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_putnbr_base(int nbr, char *base);
void			ft_putnbr_fd(int n, int fd);
void			ft_sorted_list_insert(t_list **begin_list, void *content,
					int (*cmp)());
void			ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2,
					int (*cmp)());
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(const char *sen, int c);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dest, char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strrchr(const char *sen, int c);
int				ft_strchr_int(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putstr(char *str);

/*
** gnl & gnl_utils
*/
int				gnl_strlen(const char *s);
char			*gnl_strdup(const char *s1);
char			*gnl_strjoin(char *s1, char *s2);
int				gnl_free_mem(char *s1, char *s2, int value);
int				gnl_strchr(char **rest, char **line);
int				gnl_read_file(char *temp, char **rest, char **line, int fd);
int				get_next_line(int fd, char **line);

#endif
