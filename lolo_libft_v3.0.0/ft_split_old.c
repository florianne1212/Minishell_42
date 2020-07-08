/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:00:32 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:02:21 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static char	**putword(const char *s, char c, char **str, int wcount)
{
	int	i;
	int	count;
	int	j;

	count = 0;
	i = 0;
	while (s[i] && count < wcount)
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			str[count][j] = s[i];
			j++;
			i++;
		}
		str[count][j] = '\0';
		count++;
	}
	return (str);
}

static int	wordcount(char const *s, char c)
{
	int	wcount;
	int	i;

	i = 1;
	if (s[0] == '\0')
		return (0);
	wcount = 1;
	if (s[0] == c)
		wcount = 0;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			wcount++;
		i++;
	}
	return (wcount);
}

static char	**freetab(char **str, int count)
{
	int	i;

	i = 0;
	if (count == 0)
		free(str);
	else
	{
		while (i < count)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	return (NULL);
}

static char	**str_len(char const *s, char c, char **str, int wcount)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (k < wcount && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = 0;
		while (s[i] != c && s[i])
		{
			j++;
			i++;
		}
		if (!(str[k] = (char *)malloc(sizeof(char) * (j + 1))))
			return (freetab(str, k));
		k++;
	}
	return (str);
}

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = wordcount(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	if (wcount > 0)
	{
		if (str_len(s, c, str, wcount))
			str = putword(s, c, str, wcount);
		else
			return (NULL);
	}
	if (!(str[wcount] = (char *)malloc(sizeof(char))))
		return (NULL);
	str[wcount] = NULL;
	return (str);
}
