/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:18:48 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/25 00:59:31 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//voir si on ne prend l'input que du premier terme et l'output que dans le dernier
// +++++ alternative a cote
// static void	get_piping_index_and_infile_outfile(t_shell *glob, int i)
// {
// 	glob->infile = 0;
// 	glob->outfile = 0;
// 	while (glob->cmd[i + glob->piping_index].pipe)
// 	{
// 		if (glob->cmd[i + glob->piping_index].in.path)
// 			glob->infile = glob->cmd[i + glob->piping_index].in.fd;
// 		if (glob->cmd[i + glob->piping_index].out.path)
// 			glob->outfile = glob->cmd[i + glob->piping_index].out.fd;
// 		glob->piping_index++;
// 	}
// 	if (glob->cmd[i + glob->piping_index].in.path)
// 		glob->infile = glob->cmd[i + glob->piping_index].in.fd;
// 	if (glob->cmd[i + glob->piping_index].out.path)
// 		glob->outfile = glob->cmd[i + glob->piping_index].out.fd;
// 	glob->piping_index++;
// }
//
//hypothese 1
// //infile dans 1ere instruction, outfile dans la derniere du pipe
// //il me semble que c'est celle a gerer
//

static void	get_piping_index_and_infile_outfile(t_shell *glob, int i)
{
	glob->infile = 0;
	glob->outfile = 0;
//	glob->append = 0;
	if (glob->cmd[i + glob->piping_index].in.path)
		glob->infile = glob->cmd[i + glob->piping_index].in.fd;
	while (glob->cmd[i + glob->piping_index].pipe)
		glob->piping_index++;
	if (glob->cmd[i + glob->piping_index].out.path)
	{
		glob->outfile = glob->cmd[i + glob->piping_index].out.fd;
//		if (glob->cmd[i + glob->piping_index].append)
//			glob->append = 1;
	}
	glob->piping_index++;
}

// hypothese 2

//infile n'importe ou dans le pipe, outfile n'importe ou dans le pipe
//dans ce cas je n'ai pas gere le append (trop long et hypothese probablement pas utile)
//
// static void	get_piping_index_and_infile_outfile(t_shell *glob, int i)
// {
// 	char *temp_in;
// 	char * temp_out;
//
// 	temp_in = NULL;
// 	temp_out = NULL;
// 	glob->infile = NULL;
// 	glob->outfile = NULL;
// 	while (glob->cmd[i + glob->piping_index].pipe)
// 	{
// 		if (glob->cmd[i + glob->piping_index].in.path)
// 			temp_in = glob->cmd[i + glob->piping_index].in.path;
// 		if (glob->cmd[i + glob->piping_index].out.path)
// 			temp_out = glob->cmd[i + glob->piping_index].out.path;
// 		glob->piping_index++;
// 	}
// 	if (glob->cmd[i + glob->piping_index].in.path)
// 		temp_in = glob->cmd[i + glob->piping_index].in.path;
// 	if (glob->cmd[i + glob->piping_index].out.path)
// 		temp_out = glob->cmd[i + glob->piping_index].out.path;
// 	glob->piping_index++;
// 	glob->infile = ft_strdup(temp_in);
// 	glob->outfile = ft_strdup(temp_out);
// }

void		initialize_redirections(t_shell *glob)//avec alternative open
{
	glob->tmpin = dup(STDIN_FILENO);
	glob->tmpout = dup(STDOUT_FILENO);
	if (glob->infile)
	{
		glob->fdin = glob->infile;
		// glob->fdin = open(glob->infile, O_RDONLY);
		// free(glob->infile);
		// glob->infile = NULL;
	}
	else
	{
		glob->fdin = dup(glob->tmpin);
	}
}

void		restore_in_out_and_wait(t_shell *glob, int ret)
{
	int	status;

	dup2(glob->tmpin, 0);
	dup2(glob->tmpout, 1);
	close(glob->tmpin);
	close(glob->tmpout);
	waitpid(ret, &status, 0);
	// // a voir si besoin de le faire
	// if (glob->infile)
	// {
	// 	free(glob->infile);
	// 	glob->infile = NULL;
	// }
	// if (glob->outfile)
	// {
	// 	free(glob->outfile);
	// 	glob->outfile = NULL;
	// }
}

int			tube_output_init(t_shell *glob)//alternative with open
{
	if (glob->outfile)
		glob->fdout = glob->outfile;
	// {
	// 	if (glob->append)
	// 		glob->fdout = open(glob->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 	if(!glob->append)
	// 		glob->fdout = open(glob->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	free(glob->outfile);
	// 	glob->outfile = NULL;
	// 	glob->append = 0;
	// }
	else
	{
		glob->fdout = dup(glob->tmpout);
	}
	return (0);
}

int			redir_one_piped_cmd(t_shell *glob, int j)
{
	int fdpipe[2];

	if (dup2(glob->fdin, 0) < 0)
	//perror("dup2 : ");
		return (1);
	close(glob->fdin);
	if (j == glob->piping_index - 1)
	{
		if (tube_output_init(glob))
		return (1);
	}
	else //ce n'est pas la derniere commande
	{
		if (pipe(fdpipe))
			return (1);
			//perror ("pipe :");
		glob->fdout = fdpipe[1];
		glob->fdin = fdpipe[0];
	}
	if (dup2(glob->fdout, 1) < 0)
		return (1);
		//perror("dup2 : ");
	close(glob->fdout);
	return (0);
}

int			prepare_piped_cmd(t_shell *glob, char **arg,
				char *env_path, char **path)
{
	int	ret;

	ft_change_case_instruction(arg[0]);
	if ((ret = check_and_run_builtin(glob, arg)) >= 0)
		return (ret);
	if ((ret = path_for_execve(arg[0], path, env_path)))
		return (ret);
	return (0);
}

void	control_child_piped(int n)
{
	exit(128 + n);
}


void control_back_parent_piped(int n)
{
	ft_putstr_fd("Quitter (core dumped)\n", 2);
	global_retour = 128 + n;
}

void control_C_parent_piped(int n)
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

int			fork_exec_piped_cmd(t_shell *glob, char *path, char **arg, int i)
{
	pid_t pid;

	pid = fork();
	glob->cmd[i].pid = pid;
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (piped_child_process(path, arg, glob->envirron) < 0)
			return (-1);
	}
	signal(SIGINT, control_C_parent_piped);
	signal(SIGQUIT, control_back_parent_piped);

	return ((int)pid);
}

int			pipe_and_run(t_shell *glob, int i, char *env_path)
{
	int		j;
	int		ret;
	char	*path;

	ret = 0;
	j = 0;
	get_piping_index_and_infile_outfile(glob, i);
	initialize_redirections(glob);
	while (j < glob->piping_index)
	{
		path = NULL;
		if (redir_one_piped_cmd(glob, j))
			return (1);//mais il faut restorer les redirections
		if (prepare_piped_cmd(glob, glob->cmd[i + j].cmd_arg, env_path, &path))
		{
			if (path)
				free(path);
			return (1);//la aussi restoration redirections
		}
		if ((ret = fork_exec_piped_cmd(glob, path, glob->cmd[i + j].cmd_arg,
				i + j)) < 0)
		{
			free(path);
			return (1);//restorer redirections|
		}
		free(path);
		j++;
	}
	restore_in_out_and_wait(glob, ret);
	return (0);
}

int			ft_run_commands(t_shell *glob)
{
	int		i;
	int		ret;
	char	*env_path;

	i = 0;
	while (i <= glob->cmd_index)
	{
		env_path = ft_getenv(glob->list_env, "PATH");
		glob->envirron = env_create_array(glob->list_env, glob->envirron);
		if (glob->cmd[i].pipe)
		// bloc de pipes
		{
			glob->piping_index = 0;
			ret = pipe_and_run(glob, i, env_path);
			i += glob->piping_index;
		}
		else //simple bloc
		{
			ret = ft_run_simple_command(glob, i, env_path);
			i++;
		}
		env_destroy_array(glob->envirron);
		free(env_path);
	}
	return (ret);
}

int			ft_run_commands2(int i, int index, t_shell *glob)
//a priori c'est dans cette fonction que l'on doit avoir le code de retour
{
	int		ret;
	char	*env_path;

	glob->exit_code = global_retour;
	global_retour = 0;
	while (i <= index)
	{
		env_path = ft_getenv(glob->list_env, "PATH");
		glob->envirron = env_create_array(glob->list_env, glob->envirron);
		if (glob->cmd[i].pipe)
		// bloc de pipes
		{
			glob->piping_index = 0;
			ret = pipe_and_run(glob, i, env_path);
			i += glob->piping_index;
		}
		else //simple bloc
		{
			ret = ft_run_simple_command(glob, i, env_path);
			i++;
		}
		if (global_retour ==  0)
			global_retour = ret;
		env_destroy_array(glob->envirron);
		free(env_path);
	}
	return (ret);
}
