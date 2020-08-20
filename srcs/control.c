/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	manage_control()
{
	global_retour = 0;
	signal(SIGINT, control_c);
	signal(SIGQUIT, control_back);
}

/*
** fonction qui gere quand control c est envoye
** la fonction dvra stocker 130 pour echo $?
*/

void	control_c(int i)
{
	int p;

	p = 0;
	if (glob.signal == 0)
	{
		ft_putstr("\b\b  \b\b\n$>");
	}
	else
	{
		while (glob.cmd[p].pid)
		{
			kill(glob.cmd[p].pid, i);
			p++;
		}
		ft_putstr("\n");
	}
	global_retour = 128 + i;
}

/*
** fonction qui gere quand control backslah est envoye
** la fonction dvra stocker 131 pour echo $?
*/

void	control_back(int i)
{
	int p;

	p = 0;
	if (glob.signal == 0)
	{
		ft_putstr("\b\b  \b\b");
	}
	else
	{
		while (glob.cmd[p].pid)
		{
			kill(glob.cmd[p].pid, i);
			p++;
		}
		ft_putstr("Quit : 3\n");
	}
	global_retour = 128 + i;
}
