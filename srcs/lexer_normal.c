/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
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
	while (s[i + j + p] != '\0' && e == 0)
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
	while (s[i + h] != '\0' && ft_isspace(s[i + h]) == 0)
		h++;
	if(!(str = malloc(sizeof(char) * (h + 1))))
		return (NULL);
	h = 0;
	while (s[i + h] != '\0' && ft_isspace(s[i + h]) == 0)
	{
		str[h] = s[i + h];
		h++;
	}
	str[h] = '\0';
	printf("-%s-",str);
	s1 = ft_getenv(glob->list_env, str);
	//print_list(glob->list_env);
	printf("_%s_", s1);
	glob->lex->e = h;
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
	j = 0;
	while (s[i + j + p] != '\0' && e == 0)
	{
		//if (s[i + j + p + 1] =='$' && s[i + j + p] == '\\')
		//	printf("env");
		if (s[i + j + p] == '$')
		{
			s2 = env_finder(s,(i + j + p),glob);
			//str = ft_strjoin(str, s2);
			//j = glob->lex->e;
		}
		if (s[i + j + p] == '\\' /*&& s[i + j + p + 1] == '\\'*/)
			p++;
		//if (ft_strchr_int("\"\'$", s[i + j + p + 1]) == 1 && s[i + j + p] == '\\')
		//	p++;
		//if (ft_strchr_int("\"\'$", s[i + j + p + 1]) == 0 && s[i + j + p] != '\\')
		//	e = 1;
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
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		return (j);
	}
	return (0);
}