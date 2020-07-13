/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 01:34:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/13 13:53:12 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *glob, int fd, char **arg)
{
	int	i;
	int ret;

	ret = 0;
	i = 1;
	while (arg[i])
	{
		if ((ft_unsetenv(&glob->list_env, arg[i]) == -1))
		{
			ft_putstr_fd("minishell: unset : `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
