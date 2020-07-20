/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:19:16 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/20 12:24:04 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// pid_t create_process(void)
// {
// 	pid_t pid;

// 	errno = 0;
// 	pid = fork();
// 	while (pid == -1 && errno == EAGAIN)
// 		pid = fork();
// 	return (pid);
// }

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
			i = max;//revient a faire break
		i++;
	}
	split_destructor(paths);
	return (path);
}

int		no_command_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	errno = ENOENT;
	return (1);
}

void	ft_change_case_instruction(char *instruction)
{
	int	i;

	i = 0;
	if (instruction[0] == '.')
		return ;
	if (instruction[0] == '/')
		return ;
	while (instruction[i])
	{
		if (instruction[i] > 64 && instruction[i] < 91)
			instruction[i] += 32;
		i++;
	}
}

//renvoie 1 si erreur

int		path_for_execve(char *file, char **path, char *env_path)
{
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
			return (no_command_found(file));
	}
	return (0);
}

// int		fork_and_run_command(t_shell *glob, char *path, char **arg, char **env)
// {
// 	pid_t pid;

// 	if((pid = create_process()) == -1)
// 		return (1);
// 	if (pid == 0) /*child process*/
// 		execution
// 	else /*father process*/
// 	{
// 		attente retour fils avec prompt
// 	}



// 	return (0);
// }
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
	printf("tout s'est arrete");
	free(path);
	return (ret);
}

//passer arg[0] en minuscules DONE
//chercher si builtin et run builtin DONE
// chercher si path absolu (commence par /) DONE
//chercher si path relatif (commence par .) DONE
//chercher dans PATH si commande existe WIP et prometteur
//retourner une erreur si aucun processus ok DONE
//creer le tableau envDONE
//lancer la commande avec  execve DONE
//checker si  chemin relatif et absolus sont valides
