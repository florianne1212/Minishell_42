/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 01:34:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/12 02:00:12 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *glob, int fd, char **arg)
{
	int	i;
	int ret;

	if (!arg[1])
	{
		ft_putendl_fd("unset: not enough arguments", 1);
		return (1);
	}
	i = 1;
	ret = 0;
	while (arg[i])
	{
		if ((ft_unsetenv(&glob->list_env, arg[i]) == -1) && ret == 0)
		{
			ft_putstr_fd("unset : ", fd);
			ft_putstr_fd(arg[i], fd);
			ft_putendl_fd(": invalid parameter name", fd);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
