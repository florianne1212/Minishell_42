/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_rel_to_abs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:45:14 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/15 16:45:49 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*change_rel_to_abs(char *rel)
{
	char	*abs;
	t_list	*absolute;
	char	**relative;

	absolute = NULL;
	relative = NULL;
	abs = NULL;
	if (!(path_create_data(rel, &relative, &absolute)))
		return (path_free_data(absolute, relative, NULL));
	if (!(create_path_list(&absolute, relative)))
		return (path_free_data(absolute, relative, NULL));
	if (!(abs = create_abs_str(absolute)))
		return (path_free_data(absolute, relative, NULL));
	return (path_free_data(absolute, relative, abs));
}
