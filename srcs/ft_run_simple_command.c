/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:19:16 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/16 15:21:27 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** ------Check and run builtin--------
** Check if the instruction is one of the builtin and run it
** Return -1 if not a built in, 1 if error in builtin, 0 if success
*/

int		check_and_run_builtin(t_shell *glob, char **arg)
{
	int	ret;

	ret = -1;
	if (!(ft_strcmp(arg[0], "cd")))
		ret = builtin_cd(glob, glob->fd, arg);
	else if (!(ft_strcmp(arg[0], "echo")))
		ret = builtin_echo(glob, glob->fd, arg);
	else if (!(ft_strcmp(arg[0], "env")))
		ret = builtin_env(glob, glob->fd, arg);
	else if (!(ft_strcmp(arg[0], "export")))
		ret = builtin_export(glob, glob->fd, arg);
	else if (!(ft_strcmp(arg[0], "pwd")))
		ret = builtin_pwd(glob, glob->fd, arg);
	else if (!(ft_strcmp(arg[0], "unset")))
		ret = builtin_unset(glob, glob->fd, arg);
	return (ret);
}

/*
** --- create command path ------
** Create absolute path with path from $PATH and command name
** returns NULL if error
*/

char	*create_command_path(char *env_path, char *command)
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

char	*ft_search_env_path(char *env_paths, char *command)
{
	char		*path;
	char		**paths;
	int			i;
	int			max;
	struct stat	s_bufstat;

	path = NULL;
	i = 0;
	if (!(paths = ft_split(env_paths, ':')))
		return (errno_return_str(ENOMEM, NULL));
	max = nbr_of_path(paths);
	while (paths[i])
	{
		if (path)
			free(path);
		if (!(path = create_command_path(paths[i], command)))
			return (destroy_split_errno_ret_str(paths, ENOMEM, NULL));
		if (!(stat(path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode))
			i = max - 1;
		i++;
	}
	split_destructor(paths);
	if (!(!(stat(path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode)))
		return (free_path_null(&path));
	return (path);
}

/*
** --------path for execve--------
** create a valid absolute path for execve
** return 0 for success, 1 if error
*/

int		path_for_execve(char *file, char **path, char *env_path)
{
	struct stat	s_bufstat;

	ft_memset(&s_bufstat, 0, sizeof(stat));
	if (file[0] == '/')
	{
		if (!(*path = ft_strdup(file)))
			return (errno_return_int(ENOMEM, 1));
	}
	else if (file[0] == '.')
	{
		if (!(*path = change_rel_to_abs(file)))
			return (errno_return_int(ENOMEM, 1));
	}
	else
	{
		if (!(*path = ft_search_env_path(env_path, file)))
			return (not_a_command(file, ": command not found"));
	}
	if (!(stat(*path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode))
		return (0);
	if (S_ISDIR(s_bufstat.st_mode))
		return (not_a_command(*path, ": is a directory"));
	return (not_a_command(file, ": No such file or directory"));
}

/*
** --------ft run simple command -----------
** checks if builtin, and if so runs it
** transforms instruction into a valid absolute path for execve
** command_arg is an array of command and arguments
** 		first elt in array is the command
**		other elts are the arguments
**		last elt of the array is NULL
** Needs the environnement variable chained list to be initialized (sort_envp)
** return 0 if success, 1 if failure
**
**-pour l'instant sortie dans glob->fd, a revoir ++++++
** REMARQUE IMPORTANTE  :  Path est a free !!!!
*/

int		ft_run_simple_command(t_shell *glob, int i, char *env_path)
{
	int		ret;
	char	*path;

	path = NULL;
	ret = 0;
	ft_change_case_instruction(glob->cmd[i].cmd_arg[0]);
	simple_redirection(glob, i);
	if ((ret = check_and_run_builtin(glob, glob->cmd[i].cmd_arg)) >= 0)
		return (ret);
	if (path_for_execve(glob->cmd[i].cmd_arg[0], &path, env_path))
	{
		if (path)
			free(path);
		return (1);
	}
	ret = fork_and_run_command(glob, path, glob->cmd[i].cmd_arg, glob->envirron);
	free(path);
	restore_in_out_simple(glob);
	return (ret);
}
