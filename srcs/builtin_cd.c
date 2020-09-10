/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:45:42 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/10 09:41:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**--------cd pipe---------
**renvoie erreurs  mais ne change pas de repertoire si cd est dans un pipe
*/
int			cd_pipe(char **arg)
{
	char	*absolute;
	char	*initial_dir;

	if (!arg[1] || (!ft_strcmp(arg[1], "~")))
		return (0);
	else if (!(ft_strcmp(arg[1], "-")))
		return (0);
	else if (arg[1][0] == '/')
		absolute = ft_strdup(arg[1]);
	else
		absolute = change_rel_to_abs(arg[1]);
	initial_dir = getcwd(NULL, 0);
	if (chdir(absolute))
		return (cd_error(arg[1], 1, initial_dir, absolute));
	else
		chdir(initial_dir);
	free(initial_dir);
	free(absolute);
	return (0);
}

/*
**--------cd error---------
**renvoie sur sortie error les message, free les eventuelles mallocs residuelles
*/

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

/*
**---------cd home------------
** gere le cas cd seul ou cd ~
*/

int			cd_home(t_list_env **env)
{
	char	*oldpath;
	char	*newpath;
	int		ret;

	ret = 0;
	oldpath = getcwd(NULL, 0);
	newpath = ft_getenv(*env, "HOME");
	if (!oldpath || !newpath)
		return (cd_error(NULL, 1, oldpath, newpath));
	if (chdir(newpath))
		return (cd_error(newpath, 1, oldpath, newpath));
	if ((ft_setenv(env, "OLDPWD", oldpath, 1)) == -1)
		ret = 1;
	free(oldpath);
	if ((ft_setenv(env, "PWD", newpath, 1)) == -1)
		ret = 1;
	free(newpath);
	return (ret);
}

/*
** ----------cd back----------------
** gere le cas cd -
*/

int			cd_back(t_list_env **env, int fd)
{
	char	*oldpath;
	char	*newpath;
	int		ret;

	ret = 0;
	oldpath = getcwd(NULL, 0);
	newpath = ft_getenv(*env, "OLDPWD");
	if (!newpath)
	{
		ft_putendl_fd("minishell: cd: \" OLDPWD \" non defini", 2);
		return (1);
	}
	if (!oldpath)
		return (cd_error(NULL, 1, oldpath, newpath));
	if (chdir(newpath))
		return (cd_error(newpath, 1, oldpath, newpath));
	if ((ft_setenv(env, "PWD", newpath, 1)) == -1)
		ret = 1;
	if ((ft_setenv(env, "OLDPWD", oldpath, 1)) == -1)
		ret = 1;
	ft_putendl_fd(newpath, fd);
	free(oldpath);
	free(newpath);
	return (ret);
}

/*
** ----------cd abs path-------------
** gere le cas general avec chemin absolu
*/

int			cd_abs_path(t_list_env **env, char *newpath, char *arg_path)
{
	char	*oldpath;
	int		ret;

	ret = 0;
	oldpath = ft_getenv(*env, "PWD");
	if (!newpath)
		return (cd_error(NULL, 1, oldpath, NULL));
	if (chdir(newpath))
		return (cd_error(arg_path, 1, oldpath, NULL));
	if ((ft_setenv(env, "OLDPWD", oldpath, 1)) == -1)
		ret = 1;
	free(oldpath);
	if ((ft_setenv(env, "PWD", newpath, 1)) == -1)
		ret = 1;
	return (ret);
}

/*
** ---------builtin cd---------
** regarde 1er argument, en fonction , envoie a home, back ou
** absolute path apres avoir transforme un eventuel chemin relatif
*/

int			builtin_cd(t_shell *glob, int fd, char **arg)
{
	char	*absolute;
	int		ret;

	if (glob->piping_index > 1)
		return(cd_pipe(arg));
	if (arg[1] && arg [2])
	{
		ft_putendl_fd("minishell: cd: trop d'arguments", 2);
		return (1);
	}
	if (!arg[1] || (!ft_strcmp(arg[1], "~")))
		return (cd_home(&glob->list_env));
	else if (!(ft_strcmp(arg[1], "-")))
		return (cd_back(&glob->list_env, fd));
	else if (arg[1][0] == '/')
		return (cd_abs_path(&glob->list_env, arg[1], arg[1]));
	else
	{
		absolute = change_rel_to_abs(arg[1]);
		ret = cd_abs_path(&glob->list_env, absolute, arg[1]);
		free(absolute);
		return (ret);
	}
	return (0);
}
