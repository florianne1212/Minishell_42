/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 17:41:44 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/09 13:33:25 by lcoiffie         ###   ########.fr       */
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
# include "libft.h"

typedef struct s_list_env	t_list_env;

struct			s_list_env
{
	char		*name;
	char		*value;
	t_list_env	*next;
};

typedef struct	s_shell
{
	t_list_env	*list_env;
}				t_shell;


//fonction que tu as peut etre deja :
/*
** var_env.c
*/
char			*find_name(char *str);
char			*find_value(char *str);
void			sort_envp(char **envp, t_shell *glob);
t_list_env		*add_link(t_list_env *list, char *str);
void			print_list(t_list_env *list);

/*
// ft_environ.c
*/
char 	*ft_getenv(t_list_env *env, const char *name);
int		ft_putenv(t_list_env **env, char *string);



// A VOIR ENSEMBLE

// enum {ECHO, ECHON, CD, PWD, EXPORT, UNSET, ENV, EXIT};

// typedef struct	s_simple_command
// {
// 	int			command;
// 	int			num_avail_arg;
// 	int			num_arg;
// 	char 		**arguments;
// }				t_simple_command;

// typedef struct	s_command
// {
// 	int			num_avail_command;
// 	int			num_simple_command;
// 	t_simple_command **simple_command;
// 	char		*outfile;
// 	char		*infile;
// 	char		*errfile;
// 	int			background;

// }				t_command;



#endif
