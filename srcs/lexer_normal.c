/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/18 23:20:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			size_to_mal(char *s, int *idx)
{
	int		j;
	int		e;
	int		p;

	e = 0;
	j = 0;
	p = 0;
	while (s[*idx + j + p] != '\0' && e == 0 && s[*idx + j + p] != '$' &&
	ft_isspace(s[*idx + j + p]) == 0)
	{
		if (ft_strchr_int("\"\'$", s[*idx + j + p]) == 0 &&
		s[*idx + j + p] == '\\')
			p++;
		if (ft_strchr_int("\"\'$", s[*idx + j + p]) == 1 &&
		s[*idx + j + p] != '\\')
			e = 1;
		j++;
	}
	return (j);
}

char		*env_finder(char *s, int i, t_shell *glob)
{
	int		h;
	char	*str;
	char	*s1;

	h = 0;
	h++;
	while (s[i + h] != '\0' && ft_isspace(s[i + h]) == 0 && s[i + h] != '\"')
		h++;
	if (!(str = malloc(sizeof(char) * (h + 1))))
		return (NULL);
	glob->lex->e = h;
	h = 0;
	i++;
	while (s[i + h] != '\0' && ft_isspace(s[i + h]) == 0 && s[i + h] != '\"')
	{
		str[h] = s[i + h];
		h++;
	}
	str[h] = '\0';
	s1 = ft_getenv(glob->list_env, str);
	return (s1);
}

char		*manage_normal(char *s, int *idx, t_shell *glob)
{
	char	c;
	char	*str;
	int		j;

	c = '\0';
	j = size_to_mal(s, idx);
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	str = ft_memset(str, '\0', *idx);
	j = 0;
	while ((c = s[*idx]) && ft_isspace(s[*idx]) == 0)
	{
		if (c == '\\' && ft_strchr("\\\"$\'", s[*idx + 1]))
			*idx += 1;
		else if (c == '$')
		{
			str = join_env(idx, s, glob, str, j);
			return (str);
		}
		else if (ft_strchr_int("|;><", s[*idx]) == 1)
		{
			str[j] = '\0';
			return (str);
		}
		else
		{
			str[j] = s[*idx];
			j++;
			*idx += 1;
		}
	}
	str[j] = '\0';
	return (str);
}

void		put_normal(int *idx, char *s, t_shell *glob)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[*idx] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_STRING;
		ttok->str = manage_normal(s, idx, glob);
		glob->lex->tokens[glob->lex->count] = ttok;
		glob->lex->count++;
//		printf("_.%s._", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
	}
}
