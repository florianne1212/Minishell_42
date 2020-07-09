/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:16:30 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/10 00:25:04 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*errno_return_str(int errnocode, char *return_value)
{
	errno = errnocode;
	return (return_value);
}

int 	errno_return_int(int errnocode, int return_value)
{
	errno = errnocode;
	return (return_value);
}

void	env_variable_destructor(t_list_env *env)
{
	if (env->name)
	{
		free(env->name);
		env->name = NULL;
	}
	if (env->value)
	{
		free(env->value);
		env->value = NULL;
	}
	free(env);
	env = NULL;
}

t_list_env 	*new_env_variable(char *str)
{
	t_list_env	*new;

	if (!(new = (t_list_env *)malloc(sizeof(t_list_env))))
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	if (!(new->name = find_name(str)) || !(new->value = find_value(str)))
	{
		env_variable_destructor(new);
		return(NULL);
	}
	return (new);
}

void	ft_lstadd_front_env(t_list_env **alst, t_list_env *new)
{
	if (alst || new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void		ft_list_remove_if_env(t_list_env **begin_list, void *content_ref,
				int (*cmp)(), void (*free_fct)(t_list_env *))
{
	t_list_env	*temp;
	t_list_env	*new;

	while ((*begin_list) && !((*cmp)((*begin_list)->name, content_ref)))
	{
		temp = *begin_list;
		*begin_list = temp->next;
		free_fct(temp);
	}
	new = *begin_list;
	while (new)
	{
		temp = new->next;
		while (temp && !((*cmp)(temp->name, content_ref)))
		{
			new->next = temp->next;
			free_fct(temp);
			temp = new->next;
		}
		new = new->next;
	}
}


// int		ft_setenv(t_list_env **env, const char *name, const char *value, int overwrite)
// {

// }



int		ft_unsetenv(t_list_env **env, const char *name)
{
	if (!name || !ft_strcmp(name, "") || ft_isinstring('=', (char*)name))
		return(errno_return_int(EINVAL, -1));
	ft_list_remove_if_env(env, (char *)name, ft_strcmp, env_variable_destructor);
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
		return(errno_return_str(EINVAL, NULL));
	while (env)
	{
		if (!(ft_strcmp(env->name, name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
** fonction putenv comme la native
** il faut aussi donner notre environnement en argument
** retourne 0 si succes, -1 si erreur
** si erreur, documentee dans errno
*/

int		ft_putenv(t_list_env **env, char *string)
{
	t_list_env	*new;

	if (!string || !ft_isinstring('=', string))
		return(errno_return_int(EINVAL, -1));
	if (!(new = new_env_variable(string)))
		return(errno_return_int(ENOMEM, -1));
	ft_lstadd_front_env(env, new);
	return(0);
}
