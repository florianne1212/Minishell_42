/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:18:48 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/13 09:58:25 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_piping_index(t_shell *glob, int i)
{
	while (glob->cmd[i + glob->piping_index].pipe)
		glob->piping_index++;
	glob->piping_index++;
}

void		initialize_redirections(t_shell *glob)
{
	//ft_putstr("coucou1\n");
	glob->tmpin = dup(0);
	glob->tmpout = dup(1);
	if (glob->infile)
	{
		glob->fdin = open(glob->infile, O_RDONLY);
		//ft_putstr("coucou2\n");
	}
	else
	{
		glob->fdin = dup(glob->tmpin);
		//ft_putstr("coucou3\n");

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
	// a voir si besoin de le faire
	if (glob->infile)
	{
		free(glob->infile);
		glob->infile = NULL;
	}
	if (glob->outfile)
	{
		free(glob->outfile);
		glob->outfile = NULL;
	}
}

//*renvoie 1 en cas d'erreur*/

int			tube_output_init(t_shell *glob, t_command *command)
{
	if (glob->outfile && command->append)
	{
		if ((glob->fdout = open(glob->outfile, O_WRONLY | O_CREAT |
				O_APPEND)) < 0)
			return (1);
	}
	else if (glob->outfile && !command->append)
	{
		if ((glob->fdout = open(glob->outfile, O_WRONLY | O_CREAT)) < 0)
			return (1);
	}
	else
	{
		glob->fdout = dup(glob->tmpout);
	}
	return (0);
}

//retour = 0 si ok, 1 si pb

int			redir_one_piped_cmd(t_shell *glob, t_command *command, int j)
{
	int fdpipe[2];

	ft_putstr("1er argument ");
	ft_putstr(command->cmd_arg[0]);
	ft_putstr("\n");
	if (dup2(glob->fdin, 0) < 0)
		return (1);
	close(glob->fdin);
	printf("j dans one piped = %d\n", j);
	if (j == glob->piping_index - 1)
	// derniere commande du pipe
	{
		ft_putstr("dernier du pipe\n");
		if (tube_output_init(glob, command))
			return (1);
	}
	else //ce n'est pas la derniere commande
	{
		ft_putstr("dans le pipe\n");
		pipe(fdpipe);
		glob->fdout = fdpipe[1];
		glob->fdin = fdpipe[0];
		//pour moi : faut il close fdpipe ?
	}
	if (dup2(glob->fdout, 1) < 0)
		return (1);
	close(glob->fdout);
	return (0);
}

int			prepare_piped_cmd(t_shell *glob, char **arg,
				char *env_path, char *path)
{
	int	ret;

	ft_change_case_instruction(arg[0]);
	if ((ret = check_and_run_builtin(glob, arg)) >= 0)
		return (ret);
	if (path_for_execve(arg[0], &path, env_path))
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
	(void) env_path;

	ret = 0;
	j = 0;
	get_piping_index(glob, i);
	//pour test de redirection
	if (glob->piping_index == 2)
	{
		glob->infile = ft_strdup("./srcs/ft_run_commands.c");
		glob->outfile = ft_strdup("lolo");
	}
	else
	{
		glob->infile = NULL;
		glob->outfile =  NULL;
	}

	//fin test redirection

	initialize_redirections(glob);
	// on tourne ensuite sur chaque i
	printf("j = %d\n", j);
	 while (j < glob->piping_index)
	{
		 path = NULL;
	 	// if (redir_one_piped_cmd(glob, &glob->cmd[i + j], j))
	 	// 	return (1);
		// printf("j = %d\n", j);

		if (redir_one_piped_cmd(glob, &glob->cmd[i + j], j))
	 		return (1);

	// 	if (prepare_piped_cmd(glob, glob->cmd[i + j].cmd_arg, env_path, path))
	// 		return (1);
	// 	if ((ret = fork_exec_piped_cmd(path, glob->cmd[i + j].cmd_arg,
	// 			glob->envirron)) < 0)
	// 		return (1);
	// 	free(path);
		printf("piping index = %d, i = %d, j = %d\n", glob->piping_index, i, j);
		ft_putstr("coucou\n");
		j++;
		printf("j = %d\n", j);

	}
	// restore_in_out_and_wait(glob, ret);
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
			ret = ft_run_simple_command(glob, glob->cmd[i].cmd_arg, env_path);
			i++;
		}
		free(env_path);
	}
	return (ret);
}
