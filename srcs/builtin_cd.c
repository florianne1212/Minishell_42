/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:45:42 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/16 22:58:08 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_error(char *str, int ret, char *old, char *new)
{
	ft_putstr_fd("cd: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
	if (old)
		free(old);
	if (new)
		free(new);
	return (ret);
}

int			cd_home(t_list_env *env)
{
	char	*oldpath;
	char	*newpath;
	int		ret;

	ret = 0;
	oldpath = getcwd(NULL, 1);
	newpath = ft_getenv(env, "HOME");
	if (!oldpath || !newpath)
		return (cd_error(NULL, 1, oldpath, newpath));
	if (chdir(newpath))
		return (cd_error(newpath, 1, oldpath, newpath));
	if ((ft_setenv(&env, "OLDPWD", oldpath, 1)) == -1)
		ret = 1;
	free(oldpath);
	if ((ft_setenv(&env, "PWD", newpath, 1)) == -1)
		ret = 1;
	free(newpath);
	return (ret);
}

int			cd_back(t_list_env *env, int fd)
{
	char	*oldpath;
	char	*newpath;
	int		ret;

	oldpath = getcwd(NULL, 1);
	newpath = ft_getenv(env, "OLDPWD");
	if (!oldpath || !newpath)
		return (cd_error(NULL, 1, oldpath, newpath));
	if (chdir(newpath))
		return (cd_error(newpath, 1, oldpath, newpath));
	if ((ft_setenv(&env, "PWD", newpath, 1)) == -1)
		ret = 1;
	if ((ft_setenv(&env, "OLDPWD", oldpath, 1)) == -1)
		ret = 1;
	ft_putendl_fd(newpath, fd);
	free(oldpath);
	free(newpath);
	return (ret);
}

int			cd_abs_path(t_list_env *env, char *newpath)
{
	char	*oldpath;
	int		ret;

	oldpath = getcwd(NULL, 1);
	if (!oldpath || !newpath)
		return (cd_error(NULL, 1, oldpath, NULL));
	if (chdir(newpath))
		return (cd_error(newpath, 1, oldpath, NULL));
	if ((ft_setenv(&env, "OLDPWD", oldpath, 1)) == -1)
		ret = 1;
	free(oldpath);
	if ((ft_setenv(&env, "PWD", newpath, 1)) == -1)
		ret = 1;
	return (ret);
}

int			builtin_cd(t_shell *glob, int fd, char **arg)
{
	char	*absolute;
	int		ret;

	if (!arg[1] || (!ft_strcmp(arg[1], "~")))
		return (cd_home(glob->list_env));
	else if (!(ft_strcmp(arg[1], "-")))
		return (cd_back(glob->list_env, fd));
	else if (arg[1][0] == '\\')
		return (cd_abs_path(glob->list_env, arg[1]));
	else
	{
		absolute = change_rel_to_abs(arg[1]);
		ft_putstr("le chemin absolu est :");
		ft_putendl_fd(absolute, 1);
		printf("absolute = %s\n", absolute);
		ret = cd_abs_path(glob->list_env, absolute);
		free(absolute);
		return (ret);
	}
	return (0);
}
