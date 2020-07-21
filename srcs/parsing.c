/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 22:15:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void    free_2d(char **s)
{
	int i;

	i = 0;
	while (ft_strcmp(s[i], "NULL") != 0)
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}



void            init_command(t_shell *glob, int i)
{
	if(!(glob->cmd[i] = malloc(sizeof(t_command))))
		return ;
	glob->cmd[i]->exec = NULL;
	if(!(glob->cmd[i]->argv = (char **)malloc(sizeof(char *) * (1))))
		return ;
	glob->cmd[i]->argv[0] = NULL;
	glob->cmd[i]->pipe = FALSE;
	glob->cmd[i]->in = NULL;
	glob->cmd[i]->out = NULL;
	//glob->cmd->append = NULL;
}

void    nb_command(t_shell *glob)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i <= glob->lex->count /* &&
	glob->lex->tokens[i]->type != TT_SEMICOLOM*/)
	{
		if (glob->lex->tokens[i]->type == TT_PIPE || glob->lex->tokens[i]->type == TT_SEMICOLOM)
			j++;
		i++;
	}
	if(!(glob->cmd = (t_command **) malloc(sizeof(t_command *) * (j + 2))))
		return;
}


void			recu_parser(t_shell *glob, int index, int cmd_nb)
{
	int i = index;
	init_command(glob, cmd_nb);
	if (glob->lex->tokens[index]->type != TT_STRING)
	{
	    ft_putstr("\n Syntax Error");
		exit(EXIT_SUCCESS);
	}
	while (i <= glob->lex->count && glob->lex->tokens[i]->type != TT_SEMICOLOM)
	{
	    if (i == index)
	        glob->cmd[cmd_nb]->exec = ft_strdup(glob->lex->tokens[i]->str);
		else if (glob->lex->tokens[i]->type == TT_IN)
		{
			if (manage_in(glob, i, cmd_nb) != 0)
				i += 1;
		}
		else if (glob->lex->tokens[i]->type == TT_OUT)
		{
		 	if (manage_out(glob, i) != 0)
		 		i += 1;
		}
	    else if (glob->lex->tokens[i]->type == TT_STRING)
			glob->cmd[cmd_nb]->argv = add_to_array(glob->cmd[cmd_nb]->argv, glob->lex->tokens[i]->str);
		
	    i++;
	}
	int k = 0;
	printf("\n cmd %i exec = %s", cmd_nb, glob->cmd[cmd_nb]->exec);
	while(glob->cmd[cmd_nb]->argv[k])
	{
		printf("\n cmd %i arg %i = %s",cmd_nb, k, glob->cmd[cmd_nb]->argv[k]);
		k++;
	}
	if(glob->cmd[0]->in != NULL)
		printf("\n cmd %i in = %s", cmd_nb,glob->cmd[cmd_nb]->in->path);
	fflush(stdout);
	if (i <= glob->lex->count && glob->lex->tokens[i]->type == TT_SEMICOLOM)
	{
		if(i + 1 <=  glob->lex->count)
			recu_parser(glob,(i + 1), (cmd_nb + 1));
	}
	else 
		return;
	//int k = 0;
	// fflush(stdout);
	// free(glob->cmd[0]);
	// free(glob->cmd);
	// fflush(stdout);
}

void			parser(t_shell *glob, int index)
{
	nb_command(glob);
	recu_parser(glob, index, 0);
}