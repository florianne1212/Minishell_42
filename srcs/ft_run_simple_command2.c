/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_simple_command2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:57:14 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/16 15:47:38 by lcoiffie         ###   ########.fr       */
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
		ret = builtin_cd(glob, 1, arg);
	else if (!(ft_strcmp(arg[0], "echo")))
		ret = builtin_echo(glob, 1, arg);
	else if (!(ft_strcmp(arg[0], "env")))
		ret = builtin_env(glob, 1, arg);
	else if (!(ft_strcmp(arg[0], "export")))
		ret = builtin_export(glob, 1, arg);
	else if (!(ft_strcmp(arg[0], "pwd")))
		ret = builtin_pwd(glob, 1, arg);
	else if (!(ft_strcmp(arg[0], "unset")))
		ret = builtin_unset(glob, 1, arg);
	else if (!(ft_strcmp(arg[0], "exit")))
		ret = builtin_exit(glob, 1, arg);
	return (ret);
}

/*
** ------not a command-------
** dispays message if the path is not a valid regular file
*/

int		not_a_command(char *command, char *str, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(str, 2);
	errno = ENOENT;
	return (ret);
}

/*
** -------ft change case instruction--------
** change capital letters in a single command
** no change of letter in absolute or relative paths
*/

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

/*
** ----------nb of path--------------
** calculate number of different paths in PATH env variable
*/

int		nbr_of_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

/*
**-----------free path null---------------
**free path variable and send back NULL
*/

char	*free_path_null(char **path)
{
	free(*path);
	*path = NULL;
	return (NULL);
}
