/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <sys/errno.h>
# include <string.h>
# include "libft.h"


typedef struct	s_list_env
{
	char		*name;
	char		*value;
	struct s_list_env	*next;
}				t_list_env;

typedef struct s_lex
{
	int			width;
	int			height;
	int			i;
}				t_lex;


typedef struct	s_simple_command
{
	int			command; //nom commande argument 0
	int			num_arg; 
	char 		**arguments;
	char		*outfile;
	char		*infile;
}				t_simple_command;

typedef struct	s_command
{
	int			num_simple_command;
	t_simple_command **simple_command;
	char		*outfile;
	char		*infile;
//	char		*errfile;
//	int			background;
}				t_command;

typedef struct	s_shell
{
	char		**env;
	int			retour; //echo $?
	char		**line;
	int			error;
	t_lex		*lex;
	t_list_env	*list_env;
	t_command	*command;
}				t_shell;

void			sort_envp(char **envp, t_shell *glob);
void			control_c(int i);
void			control_back(int i);

//fonction que tu as peut etre deja :
t_list_env		*add_link(t_list_env *list, char *str);
void			print_list(t_list_env *list);

char 	*ft_getenv(t_list_env *env, const char *name);
int		ft_putenv(t_list_env **env, char *string);
int		ft_unsetenv(t_list_env **env, const char *name);
int		ft_setenv(t_list_env **env, const char *name, const char *value,
				int overwrite);

/*
// errno_gestion.c
*/
char		*errno_return_str(int errnocode, char *return_value);
int			errno_return_int(int errnocode, int return_value);

/*
// env_list_gestion.c
*/
void		env_variable_destructor(t_list_env *env);
t_list_env	*new_env_variable(char *str);
void		ft_lstadd_front_env(t_list_env **alst, t_list_env *new);
void		ft_list_remove_if_env(t_list_env **begin_list, void *content_ref,
				int (*cmp)(), void (*free_fct)(t_list_env *));
t_list_env	*ft_list_find_env(t_list_env *begin_list, void *content_ref,
				int (*cmp)());
/*
// builtin_env.c
*/
int			builtin_env(t_shell *glob, int fd, char **arg);

/*
// builtin_pwd.c
*/
int			builtin_pwd(t_shell *glob, int fd, char **arg);

/*
// builtin_echo.c
*/
int			builtin_echo(t_shell *glob, int fd, char **arg);

/*
// builtin_export.c
*/
int			builtin_export(t_shell *glob, int fd, char **arg);

/*
// builtin_unset.c
*/
int			builtin_unset(t_shell *glob, int fd, char **arg);

/*
// builtin_cd.c
*/
int			builtin_cd(t_shell *glob, int fd, char **arg);

char			*find_value(char *str);

char			*find_name(char *str);

#endif
