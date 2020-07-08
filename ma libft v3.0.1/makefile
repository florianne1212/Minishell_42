SRCS		= 	ft_atoi.c \
				ft_isprint.c \
				ft_memset.c \
				ft_strdup.c \
				ft_strnstr.c \
				ft_bzero.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_strjoin.c \
				ft_strrchr.c \
				ft_calloc.c \
				ft_memccpy.c \
				ft_putendl_fd.c \
				ft_strlcat.c \
				ft_strtrim.c \
				ft_isalnum.c \
				ft_memchr.c \
				ft_putnbr_fd.c \
				ft_strlcpy.c \
				ft_substr.c \
				ft_isalpha.c \
				ft_memcmp.c \
				ft_putstr_fd.c \
				ft_strlen.c \
				ft_tolower.c \
				ft_isascii.c \
				ft_memcpy.c \
				ft_split.c \
				ft_strmapi.c \
				ft_toupper.c \
				ft_isdigit.c \
				ft_memmove.c \
				ft_strchr.c \
				ft_strncmp.c \
				ft_putnbr_base.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_itoa_base.c \
				ft_itoa_base_long.c \
				ft_isinstring.c \
				get_next_line_utils.c \
				get_next_line.c \
				ft_isspace.c \
				ft_strcmp.c \
				ft_create_elem.c \
				ft_list_at.c \
				ft_list_clear.c \
				ft_list_find.c \
				ft_list_foreach_if.c \
				ft_list_foreach.c \
				ft_list_last.c \
				ft_list_merge.c \
				ft_list_push_back.c \
				ft_list_push_front.c \
				ft_list_push_strs.c \
				ft_list_remove_if.c \
				ft_list_reverse_fun.c \
				ft_list_reverse.c \
				ft_list_size.c \
				ft_list_sort.c \
				ft_sorted_list_insert.c \
				ft_sorted_list_merge.c \
				ft_putstr.c

SRCS_B		=

H_PATH		= 	./includes/libft.h \

OBJS		= ${SRCS:.c=.o}

OBJS_B		= ${SRCS_B:.c=.o}

CC		= gcc

RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a

.c.o:
			${CC} ${CFLAGS} -c $< -I ${H_PATH} -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar -crs ${NAME} ${OBJS}

all:		${NAME}

bonus:		${OBJS_B} ${OBJS}
			ar -crs ${NAME}	${OBJS}	${OBJS_B}


clean:
			${RM} ${OBJS} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re bonus
