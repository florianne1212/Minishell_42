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

/*
** clean_cmd permet de nettoyer la structure cmd
*/

void		clean_cmd(t_shell *glob, int cmd_count)
{
	int i;
	int e;

	e = 0;
	i = 0;
	while (i <= cmd_count)
	{
		e = 0;
		free(glob->cmd[i].exec);
		while (glob->cmd[i].argv[e] != NULL)
		{
			free(glob->cmd[i].argv[e]);
			e++;
		}
		free(glob->cmd[i].argv);
		i++;
	}
	free(glob->cmd);
}

/*
** lexe_s_colon permet de lexer la ligne j'usqu'au prochain point virgule
** ou a la jusqu'a la fin de la ligne
*/

int			lexe_s_colon(char *line, t_shell *glob,int  *index)
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

/*
** la fonction lex and parse permet d'envoyer en plusieurs fois les commandes
** si elles sont separee par un point virgule
*/

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
	clean_lexer(glob);
	while(index < (int)ft_strlen(line))
	{
	
		lexe_s_colon(line, glob, &index);// permet de lexer jusqu'au semi colon (";")
		cmd_index = parser(glob, cmd_count, cmd_index); // puis de parser la partie lexer
		fflush(stdout);
		clean_lexer(glob);
		index++;
		cmd_index++;
	}
	clean_cmd(glob, cmd_count);
	return(0);
}