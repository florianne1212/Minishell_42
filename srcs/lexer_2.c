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
	while (s[i] != '\0')
	{
		/*while (ft_isspace(s[i]) == 1 && s[i] != '\0')
		{
			i++;
		}
		if (ft_strch("|><;", s[i]) == 0 && s[i] != '\0')
		{
			glob->lex->nb_words++;
			while (ft_strch("|><; \n", s[i]) == 0 && s[i] != '\0')
				i++;
		}
		while (ft_isspace(s[i]) == 1 && s[i] != '\0')
		{
			i++;
		}*/
		(void)glob;
		i++;
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
	glob->lex->nb_words = nbr_words(line, glob);
	if(!(glob->lex->tokens = (t_token **)malloc(sizeof(t_token *) * (glob->lex->nb_words + 1))))
		return ;
	while (i <= glob->lex->nb_words)
	{
		glob->lex->tokens[i] = (t_token *)malloc((sizeof(t_token)));
		i++;
	}
}

t_token *put_string(char *s, t_shell *glob)
{
	int i;
	t_token *ttok;

	i = 0;
 	if(!(ttok = malloc(sizeof(t_token))))
	 	return ((t_token *)(NULL));
	while(ft_isspace(s[i]) == 1 && s[i] !='\0')
		i++;
	if (s[i] == '|' && s[i] != '\0')
	{
		ttok->type = TT_PIPE;
		ttok->str = "pipe";
		glob->lex->count++;
	}
	return (ttok);
	//(void)glob;
}

int     lexe_line(char *line, t_shell *glob)
{
   int i;

	i = 0;


	init_lex(glob, line);
	glob->lex->tokens[0] = put_string(line, glob);
	//t_token *ttok = malloc(sizeof(t_token));
	//ttok->type = TT_STRING;
	//ttok->str = "echo";
	
	//glob->lex->tokens[0]= ttok;

	printf("test %s", glob->lex->tokens[0]->str);
	fflush(stdout);
	//(void)glob;
	(void)line;
	//put_string(line);
	return(1);
}