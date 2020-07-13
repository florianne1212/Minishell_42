/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:16:30 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/10 12:29:49 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** fonction setenv comme la native
** il faut aussi donner notre environnement en argument
** retourne 0 si succes, -1 si erreur
** si erreur, documentee dans errno
*/

static int	ft_setenv2(t_list_env *new, const char *value, int overwrite)
{
	if (overwrite == 1)
	{
		free(new->value);
		if (!(new->value = ft_strdup(value)))
			return (errno_return_int(ENOMEM, -1));
	}
	return (0);
}

int			ft_setenv(t_list_env **env, const char *name, const char *value,
				int overwrite)
{
	t_list_env	*new;

	if (!name || !ft_strcmp(name, "") || ft_isinstring('=', (char*)name))
		return (errno_return_int(EINVAL, -1));
	new = ft_list_find_env(*env, (char *)name, ft_strcmp);
	if (new)
		return (ft_setenv2(new, value, overwrite));
	if (!(new = (t_list_env *)malloc(sizeof(t_list_env))))
		return (errno_return_int(ENOMEM, -1));
	new->name = NULL;
	new->value = NULL;
	if (!(new->name = ft_strdup(name)))
	{
		env_variable_destructor(new);
		return (errno_return_int(ENOMEM, -1));
	}
	if (!(new->value = ft_strdup(value)))
	{
		env_variable_destructor(new);
		return (errno_return_int(ENOMEM, -1));
	}
	ft_lstadd_front_env(env, new);
	return (0);
}

/*
** fonction unsetenv comme la native
** il faut aussi donner notre environnement en argument
** retourne 0 si succes, -1 si erreur
** si erreur, documentee dans errno
*/

int			ft_unsetenv(t_list_env **env, const char *name)
{
	if (!name || !ft_strcmp(name, "") || ft_isinstring('=', (char*)name))
		return (errno_return_int(EINVAL, -1));
	ft_list_remove_if_env(env, (char *)name, ft_strcmp,
		env_variable_destructor);
	return (0);
}

/*
** fonction getenv comme la native, protegee
** il faut aussi donner notre environnement
** retourne la valeur de la variable d'environnement recherchee ou null
** si erreur, documentee dans errno
*/

char		*ft_getenv(t_list_env *env, const char *name)
{
	if (!env)
		return (NULL);
	if (!name || !ft_strcmp(name, "") || ft_isinstring('=', (char*)name))
		return (errno_return_str(EINVAL, NULL));
	while (env)
	{
		if (!(ft_strcmp(env->name, name)))
			return (env->value);
		env = env->next;
	}
	return (errno_return_str(0, NULL));
}

/*
** fonction putenv comme la native
** il faut aussi donner notre environnement en argument
** retourne 0 si succes, -1 si erreur
** si erreur, documentee dans errno
*/

int			ft_putenv(t_list_env **env, char *string)
{
	char	*name;
	char	*value;
	int		ret;

	if (!string || !ft_isinstring('=', string))
		return (errno_return_int(EINVAL, -1));
	if (!(name = find_name(string)))
		return (errno_return_int(ENOMEM, -1));
	if (!(value = find_value(string)))
		return (errno_return_int(ENOMEM, -1));
	ret = ft_setenv(env, name, value, 1);
	free(name);
	free(value);
	return (ret);
}