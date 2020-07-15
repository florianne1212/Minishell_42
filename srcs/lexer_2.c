/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strch(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
	{
		return (1);
	}
	return (0);
}

int	nbr_words(char const *s, t_shell *glob)
{
	int		a;
	int     j;
	int		i;

	i = 0;
	a = 0;
	j = 0;
	while (s && s[i] != '\0')
	{
		while (ft_isspace(s[i]) == 1 && s[i] != '\0')
		{
			i++;
		}
		if (ft_isspace(s[i]) == 0 && s[i] != '\0')
		{
			a++;
			while (ft_isspace(s[i]) == 0 && s[i] != '\0')
			{
				if (ft_strch("|><;", s[i]) == 1)
				{
					if (ft_isspace(s[i+1]) == 0)
						a+=2;
					else
						a++;
				}
				i++;
			}
		}
		(void)glob;
	}
	return (a);
}

void	init_lex(t_shell *glob, char  *line)
{
	int i;

	i = 0;
	if(!(glob->lex = malloc(sizeof(t_lex))))
		return;
	glob->lex->nb_words = 0;
	glob->lex->tokens = NULL;
	glob->lex->count = 0;
	glob->lex->i = 0;
	glob->lex->nb_words = nbr_words(line, glob);
	//printf("\n_____%i_______", glob->lex->nb_words);
	fflush(stdout);
	if(!(glob->lex->tokens = (t_token **)malloc(sizeof(t_token *) * (glob->lex->nb_words + 1))))
		return ;

	while (i <= glob->lex->nb_words)
	{
		glob->lex->tokens[i] = (t_token *)malloc((sizeof(t_token)));
		i++;
	}
}

void		put_append(int *index, char *s, t_shell *glob)
{
	t_token	*ttok;

	if (s[*index] == '>' && s[*index + 1] == '>' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_APPEND;
		ttok->str = "append";
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
	}
}

int     lexe_line(char *line, t_shell *glob)
{
	int index;

	index = 0;
	init_lex(glob, line);
	while (line[index] != '\0')
	{	
		if (line[index] == '|')
			put_pipe(&index, line, glob);
		else if (line[index] == ';')
			put_semicolon(&index, line, glob);
		else if (line[index] == '<')
			put_input(&index, line, glob);
		else if (line[index] == '>')
		{
			if (line[index + 1] == '>')
			{
				put_append(&index, line, glob);
				index++;
			}
			else
				put_output(&index, line, glob);
		}
		else
			index += put_string(index, line, glob);
		
		//printf("_%c_", line[index]);
		index++;
	}
	return(1);
}