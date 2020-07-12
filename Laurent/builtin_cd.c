/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:45:42 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/12 16:55:53 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//attention a free oldpwd a chaque fois y compris en cas d'erreur
//et changer pwd et oldpwd, en faisant free des anciens(normalement gere par setenv)

int	builtin_cd(t_shell *glob, int fd, char **arg)
{

	return(0);
}
