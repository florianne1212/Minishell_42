/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:19:16 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/20 15:59:17 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cherche si la fonction est l'un de nos homemade builtin et l'execute le cas
** echeant
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

//renvoie NULL si erreur

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

char	*ft_search_env_path(char *env_paths, char *command)
{
	char		*path; //a free
	char		**paths;
	int			i;
	int			max;
	struct stat	s_bufstat;

	path = NULL;
	i = 0;
	max = 0;
	if (!(paths = ft_split(env_paths, ':')))
		return (errno_return_str(ENOMEM, NULL));
	while (paths[max])
		max++;
	while (paths[i])
	{
		if (path)
			free(path);
		if (!(path = create_command_path(paths[i], command)))
			return (destroy_split_errno_ret_str(paths, ENOMEM, NULL));
		if (!(stat(path, &s_bufstat)) && S_ISREG(s_bufstat.st_mode))
			i = max - 1;//revient a faire break
		i++;
	}
	split_destructor(paths);
	return (path);
}


//renvoie 1 si erreur

int		path_for_execve(char *file, char **path, char *env_path)
{
	struct stat	s_bufstat;

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
	return (not_a_command(*path, ": No such file or directory"));
}


/*
** recherche si builtin, recherche si chemin absolu ou relatif,
** puis recherche dans PATH
**-il faut que la liste chainee variables d'environmt initialisees (sort_envp)
**-la commande est passee en tant que tableau de strings de la forme :
** "commande" "arg0" "arg1" ... "NULL"
**-pour l'instant sortie dans glob->fd, a revoir ++++++
** -retour  = 0 ok ou 1 echec
*/

int		ft_run_simple_command(t_shell *glob, char **command_arg)
{
	int		ret;
	char	*path; //attention a le free, le chemin a donner a execve
	char	*env_path;

	path = NULL;
	ret = 0;
	ft_change_case_instruction(command_arg[0]);
	if ((ret = check_and_run_builtin(glob, command_arg)) >= 0)
		return (ret);
	env_path = ft_getenv(glob->list_env, "PATH");
	path_for_execve(command_arg[0], &path, env_path);
	free(env_path);
	glob->envirron = env_create_array(glob->list_env, glob->envirron);
	//ret = fork_and_run_command(glob, path, command_arg, glob->envirron);
	ret = execve(path, command_arg, glob->envirron);
	//printf("tout s'est arrete");
	free(path);
	return (ret);
}
