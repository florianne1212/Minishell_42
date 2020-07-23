/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 21:50:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			lexe_(char *line, t_shell *glob,int  *index)
{
	init_lex(glob, line);
	while (*index < (int)ft_strlen(line))
	{
		if (line[*index] == ';')
			return(1);
		else if (line[*index] == '|')
			put_pipe(index, line, glob);
		else if (line[*index] == '<')
			put_input(index, line, glob);
		else if (line[*index] == '>')
		{
			if (line[*index + 1] == '>')
				put_append(index, line, glob);
			else
				put_output(index, line, glob);
		}
		else
			put_string(index, line, glob);
		while (((*index + 1) < (int)ft_strlen(line)) &&
		ft_isspace(line[*index + 1]) == 1)
			*index += 1;
		*index += 1;
	}
	//put_end(glob);
	//printf("\nHELLO");
	//fflush(stdout);
	return (1);
}

int			lex_and_parse(char *line, t_shell *glob)
{
	int     cmd_count;
	int		i;
	int		e;
	int		index;
	int		cmd_index;

	index = 0;
	cmd_index = 0;
	e = 0;
	i = 0;
	cmd_count = 0;
	lexe_line(line, glob);  // on lex toute la ligne
	if (!(validate(glob, &cmd_count))) // on verifie en entier
	{
		printf("syntax error\n");
		return (0);
	}
	init_cmd(glob, cmd_count);
	//int j = 0;
	while(index < (int)ft_strlen(line))
	{
		lexe_(line, glob, &index);
		e = 0;
		parser(glob, cmd_count, cmd_index);
		//clean_lexer(glob);
		fflush(stdout);
		cmd_index++;
		index++;
	}
	//i = lexe_(line, glob);
	//parser(glob, cmd_count);
	printf("_____%i", i);
	fflush(stdout);
	//lex jusqu'au ;
	// parse ;
   // parser(glob, cmd_count);
	return(0);
}