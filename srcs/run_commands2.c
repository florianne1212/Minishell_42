/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:53:24 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/14 15:21:12 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**--------restore_in_out_wait_and_return--------------
** restore les fd in et fd out par defaut
** attend le retour de la derniere instruction du pipe
** renvoie le retour 0 en cas de reussite, > 0 en cas de pb
*/

int		restore_in_out_wait_and_return(t_shell *glob, int back, int ret, int i)
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
			if (glob->cmd[i + j].pid > 0)
			{
				waitpid(glob->cmd[i + j].pid, &status, 0);
				if (WIFEXITED(status) && (j == glob->piping_index - 1))
				{
					ret = WEXITSTATUS(status);
				}
			}
			j++;
		}
	}
	return (ret);
}

void	initialise_pid(t_shell *glob, int i)
{
	int j;

	j = 0;
	while (j < glob->piping_index)
	{
		glob->cmd[i + j].pid = 0;
		j++;
	}
}
