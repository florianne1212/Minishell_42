/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 10:28:53 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/31 12:28:28 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*recurs(int depth, int *ret, int fd)
{
	char	buff[1];
	char	*out;
	int		test;

	test = read(fd, buff, 1);
	if (test == 0)
		buff[0] = 0;
	if (buff[0] == '\n' || buff[0] == 0)
	{
		if (!(out = malloc(sizeof(char) * depth + 1)))
			return (0);
		out[depth] = 0;
		*ret = 1;
		if (buff[0] == 0)
			*ret = 0;
		return (out);
	}
	else
	{
		if (!(out = recurs(depth + 1, ret, fd)))
			return (0);
		out[depth] = buff[0];
	}
	return (out);
}

int		gnl2(int fd, char **out)
{
	int ret;
	char *ligne;
	char *temp;

	ligne = ft_strdup("");
	ret = 2;
	while (ret == 2)
	{
		*out = recurs(0, &ret, fd);
		temp = *out;
		*out = ft_strjoin(ligne, temp);
		free(temp);
		if (ret == 0)
		{
			ft_putstr_fd("  \b\b", 2);
			ligne = *out;
			if (!ft_strcmp(ligne, ""))
			{
				ft_putstr_fd("exit", 2);
				free(ligne);
				exit(EXIT_SUCCESS);
			}
			ret = 2;
		}
	}
	free(ligne);
	return (ret);
}
