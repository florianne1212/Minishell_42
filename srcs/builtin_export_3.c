/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:09:34 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/02 11:15:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**-----------ft swap------------
** echange 2 strings
*/

void			ft_swap(char **s1, char **s2)
{
	char		*temp;

	temp = *s2;
	*s2 = *s1;
	*s1 = temp;
}

/*
**---------ft list sort env---------
** permet d'ordonner liste chainee dans ordre alphabetiaue
*/

void			ft_list_sort_env(t_list_env **begin_list, int (*cmp)())
{
	t_list_env	*list1;
	t_list_env	*list2;

	if (!(*begin_list) || !((*begin_list)->next))
		return ;
	list1 = *begin_list;
	while (list1 && list1->next)
	{
		list2 = list1->next;
		while (list2)
		{
			if (((*cmp)(list1->name, list2->name)) > 0)
			{
				ft_swap(&list1->name, &list2->name);
				ft_swap(&list1->value, &list2->value);
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
}

/*
** --------env sorted -----------
** lorsque export utilise sans argument
** fait "env" avec liste triee
*/

void			env_sorted(t_shell *glob, int fd)
{
	t_list_env	*list;

	list = glob->list_env;
	ft_list_sort_env(&list, ft_strcmp);
	while (list != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(list->name, fd);
		if (list->value != NULL)
		{
			ft_putstr_fd("=\"", fd);
			print_value(list->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		list = list->next;
	}
}
