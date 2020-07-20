# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 09:36:12 by fcoudert          #+#    #+#              #
#    Updated: 2019/11/26 11:42:08 by fcoudert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a

SRCS	= *.c

OBJS	= ${SRCS:.c=.o}

INCLUDE = ./

RM		= rm -f 


all:	$(NAME)


$(NAME) :
	gcc -Wall -Wextra -Werror -I ${INCLUDE} -c ${SRCS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

clean:		
			/bin/rm -f ${OBJS}
			
fclean:		clean
			/bin/rm -f ${NAME}

re:			fclean all
