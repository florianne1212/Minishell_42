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

char	*env_finder(char *s, int i, t_shell *glob)
{
	int h;
	char *str;
	char *s1;

	h = 0;
	h++;
	while (s[i + h] != '\0' && ft_isspace(s[i + h]) == 0 && s[i + h] != '\"')
		h++;
	if(!(str = malloc(sizeof(char) * (h + 1))))
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
	return(s1);

}

// int			exception_quote(char *s, int i, int j, char c)
// {
// 	if (c == '\"')
// 	{
// 		if (s[i + j] == '\\' && s[i + j + 1] == '\\')
// 			i++;
// 	}
// 	return(i);
// }

int			size_to_malloc(char *s, int *i, char c)
{
	int j;
	int e;

	e = 0;
	j = 0;
	int p = 0;
	while (s[*i + j + p] != '\0' && e == 0 && s[*i + j + p] != '$')
	{
		if (s[*i + j + 1 + p] == c && s[*i + j + p] == '\\')
			p++;
		if (s[*i + j + 1 + p] == c && s[*i + j + p] != '\\')
			e = 1;
		j++;
	}
	return(j);
}

// void lexer(char *line)
// {
// 	int index;
// 	char c;

// 	index = 0;
// 	while((c = line[index]))
// 	{
// 		if (c == '"')
// 			m(line, &index);
// 		// else if ...
// 		index++;
// 	}
// }

char *join_env(int *idx, char *s, t_shell *glob, char *str, int j)
{
	char *s2;

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
		s2 = env_finder(s,(*idx),glob);
		if (s2 != NULL)
		{	
			str[j] = '\0';
			str = ft_strjoin(str, s2);
		}
		*idx += glob->lex->e;
	}
	return(str);
}

char		*ma(char *s, int *idx, t_shell *glob)
{
	char c;
	char *str;
	int j;

	c = '\0';
	j = size_to_malloc(s, idx , c);
	if(!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	str = ft_memset(str, '\0', *idx);
	j = 0;
	while((c = s[*idx]))
	{
		if (c == '\\' && ft_strchr("\\\"$", s[*idx + 1]))
			*idx += 1;
		else if (c == '$')
		{
			str = join_env(idx,s,glob,str,j);
			return(str);
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
/*
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
	
}*/

void			put_quotation(int *idx, char *s, t_shell *glob, char c)
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
		ttok->str = ma(s, idx, glob);
		//j = glob->lex->j + 1;
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		//return (j);
	}
	//return (0);
}