/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 23:00:48 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/13 23:03:51 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		control_child_piped(int n)
{
	exit(128 + n);
}

void		control_back_parent_piped(int n)
{
	ft_putstr_fd("Quitter (core dumped)\n", 2);
	g_retour = 128 + n;
}

void		control_c_parent_piped(int n)
{
	ft_putstr_fd("\n", 2);
	g_retour = 128 + n;
}
