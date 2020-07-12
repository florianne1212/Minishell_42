/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:12:11 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/11 19:47:39 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** premiere fonction est mieux car ne tient pas compte si on unset PWD
*/

int	builtin_pwd(t_shell *glob, int fd, char **arg)
{
	t_shell	*variableinutile;
	char	*pwd;

	if (arg[1])
	{
		ft_putendl_fd("pwd: too many arguments", 1);
		return (1);
	}
	pwd = getcwd(NULL, 1);
	ft_putendl_fd(pwd, fd);
	variableinutile = glob;
	free(pwd);
	return (0);
}

int	builtin_pwd2(t_shell *glob, int fd, char **arg)
{
	if (arg[1])
	{
		ft_putendl_fd("pwd: too many arguments", 1);
		return (1);
	}
	ft_putendl_fd(ft_getenv(glob->list_env, "PWD"), fd);
	return (0);
}
