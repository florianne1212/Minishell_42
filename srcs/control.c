/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/07 18:38:33 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	manage_control(t_shell *glob)
{
	glob->return_code = global_retour;
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
	ft_putstr_fd("\n$>", 2);
	global_retour = 128 + i;
}

/*
** fonction qui gere quand control backslah est envoye
** la fonction dvra stocker 131 pour echo $?
*/

void	control_back(int i)
{
	(void)i;
	ft_putstr_fd("\b\b  \b\b", 0);
}
