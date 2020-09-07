/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:49:42 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/07 14:02:22 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**------get_piping_index_and_initialize_redirection_in------------
** calcule le nombre d'instructions successives du pipe
** initialise le infile eventuel du debut de pipe
** initialise le outfile eventuel de fin de pipe
** sauvegarde fd d'entree et sortie
** initialise fdin (qu'il faudra modifier si d'autre infiles arrivent dans pipe)
*/

void		get_piping_index_and_initialize_redirection_in(t_shell *glob, int i)
{
	glob->infile = 0;
	glob->outfile = 0;
	if (glob->cmd[i + glob->piping_index].in.path)
		glob->infile = glob->cmd[i + glob->piping_index].in.fd;
	while (glob->cmd[i + glob->piping_index].pipe)
		glob->piping_index++;
	if (glob->cmd[i + glob->piping_index].out.path)
		glob->outfile = glob->cmd[i + glob->piping_index].out.fd;
	glob->piping_index++;
	glob->tmpin = dup(STDIN_FILENO);
	glob->tmpout = dup(STDOUT_FILENO);
	if (glob->infile)
	{
		glob->fdin = glob->infile;
	}
	else
	{
		glob->fdin = dup(glob->tmpin);
	}
}

/*
**--------restore_in_out_wait_and_return--------------
** restore les fd in et fd out par defaut
** attend le retour de la derniere instruction du pipe
** renvoie le retour 0 en cas de reussite, > 0 en cas de pb
*/

int			restore_in_out_wait_and_return(t_shell *glob, int back, int ret, int i)
{
	int	status;
	int	j;

	j = 0;
	dup2(glob->tmpin, 0);
	dup2(glob->tmpout, 1);
	close(glob->tmpin);
	close(glob->tmpout);
	if (back > 0)
	{
		while ((j < glob->piping_index))
		{
			waitpid(glob->cmd[i + j].pid, &status, 0);
			j++;
		}

	}
	return (ret);
}

/*
**-----------tube_output_init-----------------
** cree la sortie si c'est la derniere instruction
*/

int			tube_output_init(t_shell *glob)
{
	if (glob->outfile)
		glob->fdout = glob->outfile;
	else
	{
		glob->fdout = dup(glob->tmpout);
	}
	return (0);
}

/*
**-----------redir_one_piped_cmd---------------
** lie input et fdin
** si derniere instruction du pipe, cree la sortie
** sinon, cree le pipe
** puis lie sortie et fdout
** renvoie 0 si pas d'erreur
*/
// c'est dans cette partie la qu'on peut gerer plus finement les pipes
//les pipes sont a gerer en premier, puis les autres infiles et outfiles
//du moins je crois

int			redir_one_piped_cmd(t_shell *glob, int j)
{
	int fdpipe[2];

	if (dup2(glob->fdin, 0) < 0)
		return (1);
	close(glob->fdin);
	if (j == glob->piping_index - 1)
	{
		if (tube_output_init(glob))
			return (1);
	}
	else
	{
		if (pipe(fdpipe) < 0)
			return (1);
		glob->fdout = fdpipe[1];
		glob->fdin = fdpipe[0];
	}
	if (dup2(glob->fdout, 1) < 0)
		return (1);
	close(glob->fdout);
	return (0);
}

void		control_child_piped(int n)
{
	exit(128 + n);
}

void		control_back_parent_piped(int n)
{
	ft_putstr_fd("Quitter (core dumped)\n", 2);
	global_retour = 128 + n;
}

void		control_c_parent_piped(int n)
{
	ft_putstr_fd("\n", 2);
	global_retour = 128 + n;
}

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
*/

int			pipe_and_run(t_shell *glob, int i, char *env_path)
{
	int		j;
	int		ret;
	char	*path;
	int		back;

	j = 0;
	back = 0;
	get_piping_index_and_initialize_redirection_in(glob, i);
	while (j < glob->piping_index)
	{
		path = NULL;
		// back = 0;// a voir
		if (redir_one_piped_cmd(glob, j))
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
		j++;
	}
	return (restore_in_out_wait_and_return(glob, back, ret, i));
}

/*
**----------run commands------------
** prepare l'environnement d'une ou plusieurs commandes pipees
** lance chaque commande comprise entre deux ';'
** sauf si erreur de syntaxe signalee avant ou ^C ( mais pas ^D ou ^\)
** global_retour correspond au retour derniere commande
** on detruit l'environnement de cette serie d'instruction ainsi que ce que donnait PATH
*/

void		run_commands(int i, t_shell *glob)
{
	int		ret;
	char	*env_path;

	//glob->return_code = (unsigned char)global_retour; //a mettre plus en haut du programme
	//avant debut nouvelle ligne
	//des que c'est fait et que florianne a recupere $?, mettre global_retour a 0
	//if (global_retour != 2 && global_retour != 130)//donc si pas de faute de syntaxe ou ^C
	{
		//global_retour = 0;//est la pour mes tests
		env_path = ft_getenv(glob->list_env, "PATH");
		glob->envirron = env_create_array(glob->list_env, glob->envirron);
		glob->piping_index = 0;
		ret = pipe_and_run(glob, i, env_path);
		glob->return_code = ret;
		if (global_retour < 128)
			global_retour = 0;
		env_destroy_array(glob->envirron);
		free(env_path);
	}
	//printf("global_retour = %d\n", global_retour);
	//global_retour = 0; //a mettre autre part, c'est pour pas etre gene par ^C

	//pas de retour car on a mis le retour dans global->return_code
}
