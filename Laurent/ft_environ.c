/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:16:30 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/09 00:17:41 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		ft_setenv(t_list_env **env, const char *name, const char *value, int overwrite)
// {

// }

// int		ft_unsetenv(t_list_env **env, const char *name)
// {

// }

char		*ft_getenv(t_list_env *env, const char *name)
{
	if (!env)
		return (NULL);
	if (!name || !ft_strcmp(name, "") || ft_isinstring('=', (char*)name))
	{
		errno = EINVAL;
		return (NULL);
	}
	while (env)
	{
		if (!(ft_strcmp(env->name, name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// int		putenv(t_list_env **env, char *string)
// {

// }
