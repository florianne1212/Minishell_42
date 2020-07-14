/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_rel_to_abs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 21:28:51 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/15 01:35:46 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*path_create_data(char *rel, char ***relative, t_list **absolute)
{
	char	*temp_abs;
	char	**temp_absolute_array;
	int		i;

	i = 0;
	if (!(*relative = ft_split((const char *)rel, '/')))
		return (NULL);
	if (!(temp_abs = getcwd(NULL, 1)))
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

int			create_path_list(t_list **abs, char **rel)
{
	int		i;
	char	*str;//sera demalloque quand on clear la liste chainee

	if (!rel)
		return (0);
	i = 0;
	while (rel[i])
	{
		if ((ft_strlen(rel[i]) > 2) && (rel[i][0] == '.'))
			return (0);
		else if (!(ft_strcmp("..", rel[i])))
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

char		*change_rel_to_abs(char	*rel)
{
	//char	*abs;
	t_list	*absolute; //liste chainee A FREE
	char	**relative; //tableau de strings est malloque, A FREE
	t_list *absolute2;

	absolute = NULL;
	relative = NULL;
	if (!(path_create_data(rel, &relative, &absolute)))
		return (path_free_data(absolute, relative, NULL));
	if (!(create_path_list(&absolute, relative)))
		return (path_free_data(absolute, relative, NULL));








	// int i = 0;
	// while (relative[i])
	// {
	// 	printf("%s\n", relative[i]);
	// 	i++;
	// }
	absolute2 = absolute;
	while (absolute2)
	{
		printf("absolute : %s\n", absolute2->content);
		absolute2 = absolute2->next;
	}
	return (path_free_data(absolute, relative, NULL));// changer null pour abs
}
