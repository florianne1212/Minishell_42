# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile2                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/06 18:25:10 by lcoiffie          #+#    #+#              #
#    Updated: 2020/09/16 17:54:29 by lcoiffie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

LIBFT_A =	libft.a

COMP =		clang $(FLAGS) $(MSHELL_H) $(LIBFT_H) -c -o

FLAGS =		-Wall -Werror -Wextra

MSHELL_H =	-I includes/

LIBFT_H = 	-I libft_42/

OBJ_DIR =	obj/

SRC_DIR =	srcs/

LIB_DIR =	libft_42/

CFILE =		builtin_cd.c \
			builtin_cd2.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_export_2.c \
			builtin_export_3.c \
			builtin_pwd.c \
			builtin_unset.c \
			change_rel_to_abs.c \
			change_rel_to_abs_utils.c \
			check_redir_simple_cmd.c \
			control.c \
			control2.c \
			env_create_array.c \
			env_list_gestion.c \
			errno_gestion.c \
			ft_environ.c \
			ft_environ_utils.c \
			ft_run_simple_command.c \
			ft_run_simple_command2.c \
			funct_lexer.c \
			gnl2.c \
			init.c \
			lex_and_parse.c \
			lexer.c \
			lexer_d_quote.c \
			lexer_normal.c \
			lexer_s_quote.c \
			main.c \
			manage_array.c \
			parsing.c \
			redirections.c \
			run_commands.c \
			run_commands2.c \
			validate_line.c \
			var_env.c \
			shell_level.c \

CFIND =		$(CFILE:%=$(SRC_DIR)%)

OFILE =		$(CFILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(OFILE))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		@echo Create: Minishell Object directory

$(NAME): $(OBJ)
		@echo LIBFT START
		@make -C $(LIB_DIR)
		@echo $(LIBFT_A) CREATED
		@clang  -o $(NAME) $(addprefix $(OBJ_DIR), $(OFILE)) $(addprefix $(LIB_DIR), $(LIBFT_A)) $(FLAGS)
		@echo MINISHELL COMPLETE

$(OBJ): $(CFIND)
		@$(MAKE) $(OFILE)

$(OFILE):
		@echo Create: $(@:obj/%=%)
		@$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
		@/bin/rm -rf $(OBJ_DIR)
		@make -C $(LIB_DIR) clean
		@echo Cleaned Minishell object files

fclean: clean
		@/bin/rm -f $(NAME)
		@make -C $(LIB_DIR) fclean
		@echo Cleaned $(NAME)

re: fclean all

.PHONY: all clean fclean re

