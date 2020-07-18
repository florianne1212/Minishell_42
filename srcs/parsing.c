/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/18 23:15:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			parser(t_shell *glob)
{
    int i;

    i = 1;
    (void)glob;
    while (i <= glob->lex->count)
    {
        printf("\n ___%s___", glob->lex->tokens[i]->str);
        i++;
    }
    fflush(stdout);
    //printf
    
}