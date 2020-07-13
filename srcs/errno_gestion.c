/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:23:08 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/10 12:23:50 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*errno_return_str(int errnocode, char *return_value)
{
	errno = errnocode;
	return (return_value);
}

int			errno_return_int(int errnocode, int return_value)
{
	errno = errnocode;
	return (return_value);
}
