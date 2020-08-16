/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:18:48 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/16 19:03:08 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_piping_index_and_infile_outfile(t_shell *glob, int i)
{
	glob->infile = 0;
	glob->outfile = 0; //a voir
	while (glob->cmd[i + glob->piping_index].pipe)
	{
		if (glob->cmd[i + glob->piping_index].in.path)
			glob->infile = glob->cmd[i + glob->piping_index].in.fd;
		if (glob->cmd[i + glob->piping_index].out.path)
			glob->outfile = glob->cmd[i + glob->piping_index].out.fd;
		glob->piping_index++;
	}
	if (glob->cmd[i + glob->piping_index].in.path)
			glob->infile = glob->cmd[i + glob->piping_index].in.fd;
	if (glob->cmd[i + glob->piping_index].out.path)
		glob->outfile = glob->cmd[i + glob->piping_index].out.fd;
	glob->piping_index++;
}

void		initialize_redirections(t_shell *glob) //attention voir si ok dans suite de pipe avec les redirections
{
	glob->tmpin = dup(STDIN_FILENO);
	glob->tmpout = dup(STDOUT_FILENO);
	//printf ("tmpin = %d, tmpout = %d\n", glob->tmpin, glob->tmpout);
	if (glob->infile)
	{
		glob->fdin = glob->infile;
	//	printf ("fdin = %d\n", glob->fdin);

	}
	else
	{
		glob->fdin = dup(glob->tmpin);
		//printf ("fdin = %d\n", glob->fdin);

		//fdin est soit le fichier, soit 0
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

//*renvoie 1 en cas d'erreur*/

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

//retour = 0 si ok, 1 si pb

int			redir_one_piped_cmd(t_shell *glob, int j)
{
	int fdpipe[2];

	// ft_putstr("1er argument ");
	// ft_putstr(command->cmd_arg[0]);
	// ft_putstr("\n");
	if (dup2(glob->fdin, 0) < 0)
		//perror("dup2 : ");
		return (1);
	close(glob->fdin);
	if (j == glob->piping_index - 1)
	// derniere commande du pipe
	{
		// ft_putstr_fd("dernier argument ", 2);
		// ft_putstr_fd(command->cmd_arg[0], 2);
		// ft_putstr_fd("\n", 2);
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
		// ft_putstr_fd("yala\n", 2);

		//printf ("fdpin = %d, fdpout = %d\n", glob->fdin, glob->fdout);
		//pour moi : faut il close fdpipe ?
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
	if (path_for_execve(arg[0], path, env_path))
		return (1);
	return (0);
}

int			piped_child_process(char *path, char **arg, char **env)
{
	int	ret;

	ret = 0;
	ret = execve(path, arg, env);
	return (ret);
}

int			fork_exec_piped_cmd(char *path, char **arg, char **env)
{
	pid_t pid;

	ft_putstr_fd("on rentre dans le dur\n",2);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	//child process
	{
		if (piped_child_process(path, arg, env) < 0)
			return (-1);
	}
	return ((int)pid);
}

//on prend le bloc d'instructions

int			pipe_and_run(t_shell *glob, int i, char *env_path)
{
	int		j;
	int		ret;
	char	*path;

	ret = 0;
	j = 0;
	get_piping_index_and_infile_outfile(glob, i);
	initialize_redirections(glob);
	// on tourne ensuite sur chaque i
	 while (j < glob->piping_index)
	{
		path = NULL;
		if (redir_one_piped_cmd(glob, j))
	 		return (1);//mais il faut restorer les redirections
		if (prepare_piped_cmd(glob, glob->cmd[i + j].cmd_arg, env_path, &path))
		{
			if (path)
				free (path);
			return (1);//la aussi restoration redirections
		}
		ft_putstr_fd("on continue\n",2);
		// ft_putstr_fd("path =", 2);
		// ft_putstr_fd(path, 2);
		// ft_putstr_fd("\n", 2);

		if ((ret = fork_exec_piped_cmd(path, glob->cmd[i + j].cmd_arg,
				glob->envirron)) < 0)
		{
			free (path);
			return (1);//restorer redirections|
		}
		ft_putstr_fd("dans le pere apres commande du pipe executee\n", 2);

		free(path);
		// printf("piping index = %d, i = %d, j = %d\n", glob->piping_index, i, j);
		j++;
	}
	restore_in_out_and_wait(glob, ret);
	ft_putstr("hourra on s'en sort\n");

	return (0);
}

//retourne 0 si OK, 1 si erreur?

int			ft_run_commands(t_shell *glob)
{
	int		i;
	int		ret;
	char	*env_path;

	i = 0;
	while (i <= glob->cmd_index)
	{
	//on fait ce qu'il y a a faire entre chaque bloc d'instruction
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
		free(env_path);
	}
	return (ret);
}
