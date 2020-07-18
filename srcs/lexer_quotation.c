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

int			exception_quote(char *s, int i, int j, char c)
{
	if (c == '\"')
	{
		if (s[i + j] == '\\' && s[i + j + 1] == '\\')
			i++;
	}
	return(i);
}

int			size_to_malloc(char *s, int i, char c)
{
	int j;
	int e;

	e = 0;
	j = 0;
	int p = 0;
	while (s[i + j + p] != '\0' && e == 0 && s[i + j + p] != '$')
	{
		if (s[i + j + 1 + p] == c && s[i + j + p] == '\\')
			p++;
		if (s[i + j + 1 + p] == c && s[i + j + p] != '\\')
			e = 1;
		j++;
	}
	return(j);
}

char		*manage_quotation(char *s, int i, char c, t_shell *glob)
{
	char *str;
	char *s2;
	int j;
	int e;
	int p;

	e = 0;
	p = 0;
	j = size_to_malloc(s, i, c);
	if(!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	str = ft_memset(str, '\0', i);
	j = 0;
	while (s[i + j + p] != '\0' && e == 0)
	{
		if (s[i + j + p] == '$')
		{	
			s2 = env_finder(s,(i + j + p),glob);
			if (s2 != NULL)
			{	str[j] = '\0';
				str = ft_strjoin(str, s2);
			}
			j += glob->lex->e;
			glob->lex->j = j+p;
			return(str);
		}
		if (s[i + j + p + 1] == '\\' && s[i + j + p] == '\\')
			p++;
		else if (s[i + j + 1 + p] == c && s[i + j + p] == '\\')
			p++;
		else if (s[i + j + 1 + p] == c && s[i + j + p] != '\\' )
			e = 1;
		str[j] = s[i + j + p];
		j++;
	}
	glob->lex->j = j+p;
	str[j] = '\0';
	return(str);
	
}

int			put_quotation(int i, char *s, t_shell *glob, char c)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[i + j] != '\0' && s[i + j] == c)
	{
		j++;
		if (!(ttok = malloc(sizeof(t_token))))
			return (0);
		ttok->type = TT_STRING;
		ttok->str = manage_quotation(s, i + j, c, glob);
		j = glob->lex->j + 1;
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		return (j);
	}
	return (0);
}