/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 10:28:53 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/13 22:38:57 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*recurs(int depth, int *ret, int fd)
{
	char	buff[1];
	char	*line;
	int		test;

	if ((test = read(fd, buff, 1)) < 0)
		return (NULL);
	if (test == 0)
		buff[0] = 0;
	if (buff[0] == '\n' || buff[0] == 0)
	{
		if (!(line = malloc(sizeof(char) * depth + 1)))
			return (NULL);
		line[depth] = 0;
		*ret = 1;
		if (buff[0] == 0)
			*ret = 0;
		return (line);
	}
	else
	{
		if (!(line = recurs(depth + 1, ret, fd)))
			return (NULL);
		line[depth] = buff[0];
	}
	return (line);
}

void	gnl_case_zero(char **line, char **before_eof, int *ret)
{
	ft_putstr_fd("  \b\b", 2);
	*before_eof = *line;
	if (!ft_strcmp(*before_eof, ""))
	{
		ft_putstr_fd("exit\n", 2);
		free(*before_eof);
		*line = ft_strdup("exit");
		*ret = 1;
	}
	else
		*ret = 2;
}

int		gnl2(int fd, char **line)
{
	int		ret;
	char	*before_eof;
	char	*temp;

	before_eof = ft_strdup("");
	ret = 2;
	while (ret == 2)
	{
		if (!(*line = recurs(0, &ret, fd)))
			return (-1);
		temp = *line;
		*line = ft_strjoin(before_eof, temp);
		free(temp);
		free(before_eof);
		if (ret == 0)
			gnl_case_zero(line, &before_eof, &ret);
	}
	return (ret);
}
