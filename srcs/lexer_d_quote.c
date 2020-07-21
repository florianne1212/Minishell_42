/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/18 13:41:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			size_to_malloc(char *s, int *i, char c)
{
	int		j;
	int		e;
	int		p;

	e = 0;
	j = 0;
	p = 0;
	while (s[*i + j + p] != '\0' && e == 0 && s[*i + j + p] != '$')
	{
		if (s[*i + j + 1 + p] == c && s[*i + j + p] == '\\')
			p++;
		if (s[*i + j + 1 + p] == c && s[*i + j + p] != '\\')
			e = 1;
		j++;
	}
	return (j);
}

char		*join_env(int *idx, char *s, t_shell *glob, char *str, int j)
{
	char	*s2;

	if (s[j] == '$' && s[j + 1] == '?')
	{
		s2 = ft_itoa(glob->retour);
		if (s2 != NULL)
		{
			str[j] = '\0';
			str = ft_strjoin(str, s2);
		}
		idx += 2;
	}
	else
	{
		s2 = env_finder(s, (*idx), glob);
		if (s2 != NULL)
		{
			str[j] = '\0';
			str = ft_strjoin(str, s2);
		}
		*idx += glob->lex->e;
	}
	return (str);
}

char		*manage_d_quote(char *s, int *idx, t_shell *glob)
{
	char	c;
	char	*str;
	int		j;

	c = '\0';
	j = size_to_malloc(s, idx, c);
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	str = ft_memset(str, '\0', *idx);
	j = 0;
	while ((c = s[*idx]))
	{
		if (c == '\\' && ft_strchr("\\\"$", s[*idx + 1]))
			*idx += 1;
		else if (c == '$')
		{
			str = join_env(idx, s, glob, str, j);
			return (str);
		}
		else if (c == '"')
			return (str);
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

void		put_quotation(int *idx, char *s, t_shell *glob, char c)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[*idx] != '\0' && s[*idx] == c)
	{
		*idx += 1;
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_STRING;
		ttok->str = manage_d_quote(s, idx, glob);
		glob->lex->tokens[glob->lex->count] = ttok;
		printf("_.%s._", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
	}
}
