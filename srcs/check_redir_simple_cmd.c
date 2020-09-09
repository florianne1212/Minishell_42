/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 13:47:03 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/08 08:12:29 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/*
** ---------check_stdin_simple-----------
** check input file and create filedescriptor
*/

void	check_stdin_simple(t_shell *glob, int i)
{
	glob->tmpin = dup(STDIN_FILENO);
	if (glob->cmd[i].in.path)
	{
		glob->fdin = glob->cmd[i].in.fd;
	}
	else
	{
		glob->fdin = dup(glob->tmpin);
	}
}

/*
** ---------check_stdout_simple-----------
** check output file and create filedescriptor
*/

void	check_stdout_simple(t_shell *glob, int i)
{
	glob->tmpout = dup(STDOUT_FILENO);
	if (glob->cmd[i].out.path)
	{
		glob->fdout = glob->cmd[i].out.fd;
	}
	else
	{
		glob->fdout = dup(glob->tmpout);
	}
}

/*
** ---------restore_in_out_simple-----------
** restore default in and out
*/

void	restore_in_out_simple(t_shell *glob)
{
	dup2(glob->tmpin, STDIN_FILENO);
	dup2(glob->tmpout, STDOUT_FILENO);
	close(glob->tmpin);
	close(glob->tmpout);
}

/*
** ---------simple_redirection-----------
** redirections for simple command gestion
*/

void	simple_redirection(t_shell *glob, int i)
{
	check_stdin_simple(glob, i);
	dup2(glob->fdin, 0);
	close(glob->fdin);
	check_stdout_simple(glob, i);
	dup2(glob->fdout, 1);
	close(glob->fdout);
}
