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
    if(!(glob->com = malloc(sizeof(t_command))))
        return ;
    glob->com->exec = NULL;
    glob->com->argv = NULL;
    glob->com->pipe = FALSE;
    glob->com->in = NULL;
    glob->com->out = NULL;
    glob->com->append = NULL;
}


void			parser(t_shell *glob, int index)
{
    
    int i;

    i = 1;
    init_command(glob);
    (void)glob;
    if (glob->lex->tokens[index]->type != TT_STRING)
    {
        ft_putstr("\n Syntax Error");
    }
    while (i <= glob->lex->count)
    {
        if (i == index)
            glob->com->exec = ft_strdup(glob->lex->tokens[i]->str);
        //else if()
        //printf("\n ___%s___", glob->lex->tokens[i]->str);
        i++;
    }
    //printf("\n,,,%s,,",glob->com->exec);
    fflush(stdout);
    //printf
    
}