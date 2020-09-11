/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 01:34:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/11 12:14:29 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** -----------builtin unset--------
** unset les variables d'environnemet
*/

int	builtin_unset(t_shell *glob, int fd, char **arg)
{
	int	i;
	int ret;

	ret = 0;
	i = 1;
	(void)fd;
	while (arg[i])
	{
		if ((ft_unsetenv(&glob->list_env, arg[i]) == -1))
		{
			ft_putstr_fd("unset : `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putendl_fd("': invalid parameter name", 2);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
