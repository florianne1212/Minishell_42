/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 23:45:02 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/07 18:34:19 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** --------builtin env----------
** fonction env sans option
*/

int	builtin_env(t_shell *glob, int fd, char **arg)
{
	t_list_env *list;

	if (arg[1])
	{
		ft_putendl_fd("env: no arguments or option in minishell", 2);
		return (1);
	}
	list = glob->list_env;
	while (list != NULL)
	{
		if (list->value != NULL)
		{
			ft_putstr_fd(list->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(list->value, fd);
			ft_putstr_fd("\n", fd);
		}
		list = list->next;
	}
	return (0);
}
