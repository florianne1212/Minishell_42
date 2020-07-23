/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_gestion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:30:27 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/23 08:31:54 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** ------------env variable destructor---------------
** free un des elts de la list t_list env
*/

void		env_variable_destructor(t_list_env *env)
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

/*
** ------------new env variable -------------
** cree un nouvel elt pour  t_list_env
** a partir d'un string name=value
*/

t_list_env	*new_env_variable(char *str)
{
	t_list_env	*new;

	if (!(new = (t_list_env *)malloc(sizeof(t_list_env))))
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	if (!(new->name = find_name(str)))
	{
		env_variable_destructor(new);
		return (NULL);
	}
	if (!(new->value = find_value(str)))
	{
		env_variable_destructor(new);
		return (NULL);
	}
	return (new);
}

/*
** --------ft lstadd front env ---------------
** rajoute elt a la list d'environnement env
*/

void		ft_lstadd_front_env(t_list_env **alst, t_list_env *new)
{
	if (alst || new)
	{
		new->next = *alst;
		*alst = new;
	}
}

/*
** ----------ft list remove if env---------------
** comme ft list remove if, mais avec la t_list_env
*/

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

/*
** ---------ft list find env ------------
** recherche elt correspondant au nom dans la liste
** chainee env
*/

t_list_env	*ft_list_find_env(t_list_env *begin_list, void *content_ref,
				int (*cmp)())
{
	t_list_env	*new;

	new = begin_list;
	while (new)
	{
		if (!((*cmp)(new->name, content_ref)))
			return (new);
		new = new->next;
	}
	return (NULL);
}
