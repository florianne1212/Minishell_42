/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/18 13:41:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			size_to_mal(char *s, int i)
{
	int j;
	int e;

	e = 0;
	j = 0;
	int p = 0;
	while (s[i + j + p] != '\0' && e == 0 && s[i + j + p] != '$')
	{
		if (ft_strchr_int("\"\'$", s[i + j + p]) == 0 && s[i + j + p] == '\\')
			p++;
		if (ft_strchr_int("\"\'$", s[i + j + p]) == 1 && s[i + j + p] != '\\')
			e = 1;
		j++;
	}
	return(j);
}

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

char		*manage_normal(char *s, int i, t_shell *glob)
{
	char *str;
	char *s2;
	int j;
	int e;
	int p;

	e = 0;
	p = 0;
	j = size_to_mal(s, i);
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
		if (s[i + j + p] == '\\')
			p++;
		str[j] = s[i + j + p];
		j++;
	}
	glob->lex->j = j+p;
	str[j] = '\0';
	return(str);
	
}

int			put_normal(int i, char *s, t_shell *glob)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[i + j] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return (0);
		ttok->type = TT_STRING;
		ttok->str = manage_normal(s, i + j,glob);
		j = glob->lex->j;
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf("_.%s._", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		return (j);
	}
	return (0);
}