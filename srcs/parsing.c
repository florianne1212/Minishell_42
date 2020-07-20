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

void            init_command(t_shell *glob)
{
    if(!(glob->cmd = malloc(sizeof(t_command))))
        return ;
    glob->cmd->exec = NULL;
    glob->cmd->argv = NULL;
    glob->cmd->pipe = FALSE;
    glob->cmd->in = NULL;
    glob->cmd->out = NULL;
    //glob->cmd->append = NULL;
}

void    nb_command(t_shell *glob)
{
    int i;
    int j;

    i = 1;
    while (i <= glob->lex->count &&
    glob->lex->tokens[i]->type != TT_SEMICOLOM)
    {
        if (glob->lex->tokens[i]->type == TT_PIPE)
            j++;
        i++;
    }
    if(!(glob->cmd = malloc(sizeof(t_command *) * (j + 2))))
        return;
}


void			parser(t_shell *glob, int index)
{
    
    int i;

    i = 1;
    init_command(glob);
    nb_command(glob);
    (void)glob;
    if (glob->lex->tokens[index]->type != TT_STRING)
    {
        ft_putstr("\n Syntax Error");
    }
    while (i <= glob->lex->count)
    {
        if (i == index)
            glob->cmd->exec = ft_strdup(glob->lex->tokens[i]->str);
        //else if()
        //printf("\n ___%s___", glob->lex->tokens[i]->str);
        i++;
    }
    printf("\n,,,%s,,",glob->cmd->exec);
    fflush(stdout);
    //printf
    
}