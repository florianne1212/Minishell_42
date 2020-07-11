/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:12:11 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/11 17:09:04 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *glob, int fd, char **arg)
{
	if (arg[1])
	{
		ft_putendl_fd("pwd: too many arguments", 1);
		return (1);
	}
	ft_putendl_fd(ft_getenv(glob->list_env, "PWD"), fd);
	return (0);
}
