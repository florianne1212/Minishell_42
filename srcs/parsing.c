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

int  ft_strlen_array(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return(i);
}

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

char        **add_to_array(char **s1, char *s2)
{
	int ss1;
	int i;
	char **ss3;

	//char * == NULL;

	i = 0;
	ss3 = NULL;
	if (s1)
	{
		ss1 = ft_strlen_array(s1);
		if(!(ss3 = (char **)malloc(sizeof(char *) * (ss1 + 2))))
			return (NULL);
		while (s1[i])
		{
			ss3[i] = s1[i];
			i++;
		}
		//free_2d(s1);
		free(s1);
		ss3[i++] = ft_strdup(s2);
		ss3[i] = NULL;
	}
	return(ss3);
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
	while (i <= glob->lex->count &&
	glob->lex->tokens[i]->type != TT_SEMICOLOM)
	{
		if (glob->lex->tokens[i]->type == TT_PIPE)
			j++;
		i++;
	}
	if(!(glob->cmd = (t_command **) malloc(sizeof(t_command *) * (j + 2))))
		return;
}

char            **find_argv(t_shell *glob, int i)
{
	int j;
	int k;
	char **argv;

	j = i;
	while (j <= glob->lex->count && glob->lex->tokens[j]->type == TT_STRING)
		j++;
	j = j - i;
	printf("--%i--", j);
	if(!(argv = (char **)malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	j = i;
	k = 0;
	while (j <= glob->lex->count && glob->lex->tokens[j]->type == TT_STRING)
	{
		ft_putstr(glob->lex->tokens[j]->str);
		fflush(stdout);
		argv[k] = ft_strdup(glob->lex->tokens[j]->str);
		//printf("\n ____%s____", argv[k]);
		k++;
		j++;
	}
	argv[k] =  NULL;
	return(argv);
}

void			parser(t_shell *glob, int index)
{
	
	int i;

	i = 1;
	nb_command(glob);
	init_command(glob, 0);
	if (glob->lex->tokens[index]->type != TT_STRING)
	{
	    ft_putstr("\n Syntax Error");
	}
	while (i <= glob->lex->count)
	{
	    if (i == index)
	        glob->cmd[0]->exec = ft_strdup(glob->lex->tokens[i]->str);
		//else if (glob->lex->tokens[i]->type == TT_IN)

	    else if (glob->lex->tokens[i]->type == TT_STRING)
	        glob->cmd[0]->argv = add_to_array(glob->cmd[0]->argv, glob->lex->tokens[i]->str);
		
	    i++;
	}
	int k = 0;
	printf("\n exec = %s", glob->cmd[0]->exec);
	while(glob->cmd[0]->argv[k])
	{
		printf("\n arg %i = %s",k, glob->cmd[0]->argv[k]);
		k++;
	}
	fflush(stdout);
	free(glob->cmd[0]);
	free(glob->cmd);
	fflush(stdout);
}