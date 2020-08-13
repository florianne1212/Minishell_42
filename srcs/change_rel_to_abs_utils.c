/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_rel_to_abs_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 21:28:51 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/22 22:51:21 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** ---------path free data------------
** free le tableau de string du chemin relatif
** free la liste chainee permettant d'avoir le chemin absolu
** on retourne le string ret
*/

char		*path_free_data(t_list *list, char **str_array, char *ret)
{
	int		i;
	t_list	*tmp;

	i = 0;
	if (str_array)
	{
		while (str_array[i])
		{
			free(str_array[i]);
			str_array[i] = NULL;
			i++;
		}
		free(str_array);
		str_array = NULL;
	}
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
	return (ret);
}

/*
** -----------path create data ------------
** Cree tableau de string avec chaque elt path relatif (relative)
** prend le chemin absolu de notre position actuelle (temp abs)
** cree un tableau de string a partir de ce chemin absolu(temp absolute array)
** que l'on transforme en liste chainee
*/

char		*path_create_data(char *rel, char ***relative, t_list **absolute)
{
	char	*temp_abs;
	char	**temp_absolute_array;
	int		i;

	i = 0;
	if (!(*relative = ft_split((const char *)rel, '/')))
		return (NULL);
	if (!(temp_abs = getcwd(NULL, 0)))
		return (NULL);
	if (!(temp_absolute_array = ft_split((const char *)temp_abs, '/')))
	{
		free(temp_abs);
		return (NULL);
	}
	while (temp_absolute_array[i])
	{
		ft_list_push_front(absolute, temp_absolute_array[i]);
		i++;
	}
	free(temp_abs);
	free(temp_absolute_array);
	return ("ok");
}

/*
**---------delete list first elem--------------
** supprime 1er elt liste chainee
*/

void		delete_list_first_elem(t_list **beginlist)
{
	t_list *tmp;

	if (!(*beginlist))
		return ;
	tmp = *beginlist;
	*beginlist = tmp->next;
	free(tmp->content);
	free(tmp);
}

/*
** --------create path list--------------
** cree la liste chainee correspondant au chemin absolu
** '..' suppression elt
** '.' rien ne bouge
** sinon on ajoute nouvel elt a la liste
*/

int			create_path_list(t_list **abs, char **rel)
{
	int		i;
	char	*str;

	if (!rel)
		return (0);
	i = 0;
	while (rel[i])
	{
		if (!(ft_strcmp("..", rel[i])))
			delete_list_first_elem(abs);
		else if (ft_strcmp(".", rel[i]))
		{
			if (!(str = ft_strdup(rel[i])))
				return (0);
			ft_list_push_front(abs, str);
		}
		i++;
	}
	return (1);
}

/*
** ---------create abs str-------------
** cree le chemin absolu a partir de la liste chainee
*/

char		*create_abs_str(t_list *absolute)
{
	char	*abs;
	char	*temp;

	if (!absolute)
		return (abs = ft_strdup("/"));
	if (!(abs = ft_strdup("")))
		return (NULL);
	while (absolute)
	{
		if (!(temp = ft_strjoin(absolute->content, abs)))
		{
			free(abs);
			return (NULL);
		}
		free(abs);
		if (!(abs = ft_strjoin("/", temp)))
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		absolute = absolute->next;
	}
	return (abs);
}
