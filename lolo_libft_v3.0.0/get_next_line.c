/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:25:26 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/02/07 10:16:13 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		gnl_strchr(char **rest, char **line)
{
	int		i;
	char	*ptr_on_jump;

	i = 0;
	ptr_on_jump = *rest;
	while (ptr_on_jump[i])
	{
		if (ptr_on_jump[i] == '\n')
		{
			ptr_on_jump[i] = '\0';
			if (!(*line = gnl_strdup(ptr_on_jump)))
				return (-1);
			if (!(*rest = gnl_strdup(&ptr_on_jump[i + 1])))
				return (-1);
			gnl_free_mem(ptr_on_jump, NULL, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

int		gnl_read_file(char *temp, char **rest, char **line, int fd)
{
	int		i;
	int		j;
	char	*temp_rest;

	while ((i = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[i] = '\0';
		if (*rest)
		{
			temp_rest = *rest;
			if (!(*rest = gnl_strjoin(temp_rest, temp)))
				return (-1);
			gnl_free_mem(temp_rest, NULL, 0);
		}
		else if (!(*rest = gnl_strdup(temp)))
			return (-1);
		j = gnl_strchr(rest, line);
		if (j < 0)
			return (-1);
		if (j > 0)
			break ;
	}
	if (i > 0)
		i = 1;
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char *rest[MAX_FD] = {NULL};
	char		*temp;
	int			value;
	int			i;

	if (fd < 0 || !line || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (-1);
	if (!(temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (rest[fd] == NULL)
		if (!(rest[fd] = gnl_strdup("")))
			return (-1);
	if (rest[fd])
		if ((i = gnl_strchr(&rest[fd], line)))
			return (gnl_free_mem(temp, NULL, i));
	value = gnl_read_file(temp, &rest[fd], line, fd);
	if (value == 0 && rest[fd])
		*line = gnl_strdup(rest[fd]);
	if (value == 0)
	{
		free(rest[fd]);
		rest[fd] = NULL;
	}
	return (gnl_free_mem(temp, NULL, value));
}
