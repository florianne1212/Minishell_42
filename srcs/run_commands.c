/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:49:42 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/14 15:39:45 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**---------piped_child_process----------------
** traitement du signal dans les fils
** retour que si erreur lors de execve
*/

int			piped_child_process(char *path, char **arg, char **env)
{
	int	ret;

	ret = 0;
	signal(SIGINT, control_child_piped);
	signal(SIGQUIT, control_child_piped);
	ret = execve(path, arg, env);
	return (ret);
}

/*
**---------fork_exec_piped_cmd----------------
** renvoie -1 en cas d'erreur, sinon retourne le pid
*/

int			fork_exec_piped_cmd(t_shell *glob, char *path, int i)
{
	pid_t pid;

	pid = fork();
	glob->cmd[i].pid = pid;
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (piped_child_process(path, glob->cmd[i].cmd_arg, glob->envirron) < 0)
			return (-1);
	}
	signal(SIGINT, control_c_parent_piped);
	signal(SIGQUIT, control_back_parent_piped);
	return ((int)pid);
}

/*
**----------prepare_piped_cmd--------------
** transforme instruction en minuscules
** verifie si c'est un builtin (0 builtin ok, 1 builtinko, -1 no bultin)
** cree chemin a utiliser pour execve
** si renvoie -1, path ok
*/

int			prepare_cmd(t_shell *glob, char **arg,
				char *env_path, char **path)
{
	int	ret;

	ft_change_case_instruction(arg[0]);
	if ((ret = check_and_run_builtin(glob, arg)) >= 0)
		return (ret);
	if ((ret = path_for_execve(arg[0], path, env_path)))
		return (ret);
	return (-1);
}

/*
** -------------pipe_and_run---------------
** renvoie 0 en cas de succes
** le retour de bash en cas d'echec ou d'interruption
** lance commandes du pipe une a une
** apres verification builtin et chemin
** puis fork pour exec la commande
** attend la fin de toutes les commandes du pipe
** et restore stdin et stdout
*/

int			pipe_and_run(t_shell *glob, int i, char *env_path)
{
	int		j;
	int		ret;
	char	*path;
	int		back;

	j = -1;
	back = 0;
	if (get_piping_index_and_initialize_redirection_in(glob, i))
		return (1);
	while (++j < glob->piping_index)
	{
		path = NULL;
		if (redir_one_piped_cmd(glob, j, i))
			return (restore_in_out_wait_and_return(glob, 0, 1, i));
		ret = prepare_cmd(glob, glob->cmd[i + j].cmd_arg, env_path, &path);
		if (ret < 0)
		{
			ret = 0;
			if ((back = fork_exec_piped_cmd(glob, path, i + j)) < 0)
				ret = 1;
		}
		if (path)
			free(path);
	}
	return (restore_in_out_wait_and_return(glob, back, ret, i));
}

/*
**----------run commands------------
** prepare l'environnement d'une ou plusieurs commandes pipees
** lance chaque commande comprise entre deux ';'(pipe and run)
** return_code correspond au retour derniere commande
** on detruit l'environnement de cette serie d'instruction
** ainsi que ce que donnait PATH
*/

void		run_commands(int i, t_shell *glob)
{
	int		ret;
	char	*env_path;

	if (glob->cmd[i].exec && ft_strlen(glob->cmd[i].exec) != 0)
	{
		env_path = ft_getenv(glob->list_env, "PATH");
		glob->envirron = env_create_array(glob->list_env, glob->envirron);
		glob->piping_index = 0;
		ret = pipe_and_run(glob, i, env_path);
		glob->return_code = ret;
		if (g_retour < 128)
			g_retour = 0;
		env_destroy_array(glob->envirron);
		free(env_path);
	}
	else
	{
		if (glob->cmd[i].error == 1)
			g_retour = 1;
	}
}
