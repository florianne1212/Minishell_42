/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:45:42 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/13 01:24:42 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//attention a free oldpwd a chaque fois y compris en cas d'erreur
//et changer pwd et oldpwd, en faisant free des anciens(normalement gere par setenv)

static int	errorcd(int fd, char *str, int ret)
{
	ft_putstr_fd("cd: no such file or directory: ", fd);
	ft_putendl_fd(str, fd);
	return ret;
}
int			home(t_list_env *env, int fd)
{
	char	*oldpath;
	char	*newpath;

	oldpath = getcwd(NULL, 1);
	newpath = ft_getenv(env, "HOME");
	chdir(newpath);
	ft_setenv(&env, "OLDPWD", oldpath, 1);
	free(oldpath);
	ft_setenv(&env, "PWD", newpath, 1);
	free(newpath);
	return (0);
}

int			builtin_cd(t_shell *glob, int fd, char **arg)
{
	char	*oldpath;
	char	*newpath;

	if (arg[2])
		return(errorcd(fd,arg[1],1));
	if (!arg[1])
		return(home(glob->list_env, fd));
	oldpath = getcwd(NULL, 1);





	return(0);
}
