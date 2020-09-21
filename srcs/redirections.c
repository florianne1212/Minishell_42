/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 23:33:49 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/14 00:00:38 by lcoiffie         ###   ########.fr       */
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

int			get_piping_index_and_initialize_redirection_in(t_shell *glob, int i)
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
	if ((glob->tmpin = dup(STDIN_FILENO)) < 0)
		return (1);
	if ((glob->tmpout = dup(STDOUT_FILENO)) < 0)
		return (1);
	if (glob->infile)
	{
		glob->fdin = glob->infile;
	}
	else
	{
		if ((glob->fdin = dup(glob->tmpin)) < 0)
			return (1);
	}
	initialise_pid(glob, i);
	return (0);
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
		if ((glob->fdout = dup(glob->tmpout)) < 0)
			return (1);
	}
	return (0);
}

/*
**------------redir_in--------------
** gere redirection in
** si premier terme du pipe, correspond a glob->fdin
** sinon on change si redirection existe
*/

int			redir_in(t_shell *glob, int j, int i)
{
	if (dup2(glob->fdin, 0) < 0)
		return (1);
	close(glob->fdin);
	if (glob->cmd[i + j].in.path && (j > 0))
	{
		glob->fdin = glob->cmd[i + j].in.fd;
		if (dup2(glob->fdin, 0) < 0)
			return (1);
		close(glob->fdin);
	}
	return (0);
}

/*
**------------redir_out--------------
** gere redirection out
** si dernier terme du pipe, correspond a glob->fdout
** sinon on change si redirection existe
*/

int			redir_out(t_shell *glob, int j, int i)
{
	if (dup2(glob->fdout, 1) < 0)
		return (1);
	close(glob->fdout);
	if (glob->cmd[i + j].out.path && (j != glob->piping_index - 1))
	{
		glob->fdout = glob->cmd[i + j].out.fd;
		if (dup2(glob->fdout, 1) < 0)
			return (1);
		close(glob->fdout);
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

int			redir_one_piped_cmd(t_shell *glob, int j, int i)
{
	int fdpipe[2];

	if (redir_in(glob, j, i))
		return (1);
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
	if (redir_out(glob, j, i))
		return (1);
	return (0);
}
