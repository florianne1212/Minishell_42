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

# include <stdio.h>
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

void			sort_envp(char **envp, t_shell *glob);

//fonction que tu as peut etre deja :
t_list_env		*add_link(t_list_env *list, char *str);
void			print_list(t_list_env *list);

#endif
