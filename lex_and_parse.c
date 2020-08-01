/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/08/01 20:02:23 by lcoiffie         ###   ########.fr       */
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
		while (glob->cmd[i].argv[e] != NULL)
		{
			free(glob->cmd[i].argv[e]);
			glob->cmd[i].argv[e] = NULL;
			e++;
		}
		/*if (glob->cmd[i].cmd_arg[0] != NULL)*/

		//free(glob->cmd[i].cmd_arg[0]);
		free(glob->cmd[i].exec);
		free(glob->cmd[i].cmd_arg);
		//free(glob->cmd[i].cmd_arg);
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
		while (((*index) < (int)ft_strlen(line)) &&
		ft_isspace(line[*index]) == 1)
			*index += 1;
	}
	return (1);
}

void		arg_in_tab(int i, int cmd_index, t_shell *glob)
{
	char ** test;
	int e;
	e = 0;

	while (i <= cmd_index)
	{
		e = 0;
		test = glob->cmd[i].argv;
		//if (i == 0)
		free(glob->cmd[i].cmd_arg);
		glob->cmd[i].cmd_arg = add_front_to_array(glob->cmd[i].argv, glob->cmd[i].exec);
		ft_run_simple_command(glob, glob->cmd[i].cmd_arg);
		//la ligne que j'ai change//
		i++;
	}
	fflush(stdout);
}

/*
** la fonction lex and parse permet d'envoyer en plusieurs fois les commandes
** si elles sont separee par un point virgule
*/

int			lex_and_parse(char *line, t_shell *glob)
{
	int     cmd_count;
	int		i;
	// int		e;
	int		index;
	int		cmd_index;

	index = 0;
	cmd_index = 0;
	// e = 0;
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
		i = cmd_index;
		lexe_s_colon(line, glob, &index);// permet de lexer jusqu'au semi colon (";")
		cmd_index = parser(glob, cmd_count, cmd_index); // puis de parser la partie lexer
		fflush(stdout);
		clean_lexer(glob);
		arg_in_tab(i, cmd_index, glob);
		index++;
		cmd_index++;
	}
	clean_cmd(glob, cmd_count);
	return(0);
}