/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:19:16 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/16 15:48:00 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** --- create command path ------
** Create absolute path with path from $PATH and command name
** returns NULL if error
*/

char		*create_command_path(char *env_path, char *command)
{
	char	*temp;
	char	*path;

	if (!(temp = ft_strjoin(env_path, "/")))
		return (NULL);
	if (!(path = ft_strjoin(temp, command)))
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (path);
}

/*
** -----ft search env path--------
** explore the different path from $PATH, with the command
** check if the status of this path is a regular file, and returns it
** returns NULL if no path found with this instruction
*/

char		*ft_search_env_path2(char *env_paths, char *command)
{
	char		*path;
	char		**paths;
	int			i;
	int			max;
	struct stat	s_bufstat;

	path = NULL;
	i = -1;
	if (!(paths = ft_split(env_paths, ':')))
		return (errno_return_str(ENOMEM, NULL));
	max = nbr_of_path(paths);
	while (paths[++i])
	{
		if (path)
			free(path);
		if (!(path = create_command_path(paths[i], command)))
			return (destroy_split_errno_ret_str(paths, ENOMEM, NULL));
		if (!(stat(path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode))
			i = max - 1;
	}
	errno = 0;
	split_destructor(paths);
	if (!(!(stat(path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode)))
		return (free_path_null(&path));
	return (path);
}

char		*ft_search_env_path(char *env_paths, char *command)
{
	char		*path;
	char		*temp;
	struct stat	s_bufstat;

	if (env_paths)
		return (ft_search_env_path2(env_paths, command));
	else
	{
		path = getcwd(NULL, 0);
		temp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(temp, command);
		free(temp);
		if (!(!(stat(path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode)))
			return (free_path_null(&path));
		return (path);
	}
	return (path);
}

/*
**---------create the path---------
** create path for the command
*/

static void	create_the_path(char *file, char **path)
{
	if (file[0] == '/')
		*path = ft_strdup(file);
	else if (file[0] == '.')
		*path = change_rel_to_abs(file);
}

/*
** --------path for execve--------
** create a valid absolute path for execve
** return 0 for success, 1 if error
*/

int			path_for_execve(char *file, char **path, char *env_path)
{
	struct stat	s_bufstat;

	ft_memset(&s_bufstat, 0, sizeof(stat));
	if ((file[0] == '/') || (file[0] == '.'))
	{
		create_the_path(file, path);
		if (!(*path))
			return (errno_return_int(ENOMEM, 1));
	}
	else
	{
		if (!(*path = ft_search_env_path(env_path, file)))
			return (not_a_command(file, ": commande introuvable", 127));
	}
	s_bufstat.st_mode = 0;
	if (!(stat(*path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode))
	{
		if (s_bufstat.st_mode & S_IXUSR)
			return (0);
		return (not_a_command(file, ": Permission non accordee", 126));
	}
	if (S_ISDIR(s_bufstat.st_mode))
		return (not_a_command(file, ": est un dossier", 126));
	return (not_a_command(file, ": Aucun fichier ou dossier de ce type", 127));
}
