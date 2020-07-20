/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 23:45:02 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/12 01:03:27 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *glob, int fd, char **arg)
{
	t_list_env *list;

	if (arg[1])
	{
		ft_putendl_fd("env: no arguments or option in minishell", 1);
		return (1);
	}
	list = glob->list_env;
	while (list != NULL)
	{
		ft_putstr_fd(list->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(list->value, fd);
		ft_putstr_fd("\n", fd);
		list = list->next;
	}
	return (0);
}
