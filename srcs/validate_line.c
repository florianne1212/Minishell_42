/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 22:15:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** la fonction meet permet de verifier si le type
** rencontree correspond a ce qu'on attend
** elle retourne 1 si vrai et 0 si faux
*/

static int		meet(int expect, t_token *tok, t_token_type type)
{
	return ((expect & type) && tok->type == type);
}

/*
** La fonction validate_cond permet de verifier les conditions
** de validate et verifie si notre ligne de commande est valide
*/

void			validate_cond_bis(t_token *tok)
{
	g_retour = 2;
	ft_putstr_fd("minishell: erreur de syntaxe près du symbole inattendu << ",
	2);
	ft_putstr_fd(tok->str, 2);
	ft_putstr_fd(" >>\n", 2);
}

void			validate_cond(int idx, t_shell *glob, int *expect, int *cmd_c)
{
	t_token		*tok;

	while (idx < glob->lex->count)
	{
		tok = glob->lex->tokens[idx];
		*cmd_c += (tok->type == TT_PIPE || tok->type == TT_SEMICOLOM);
		if (meet(*expect, tok, TT_STRING))
			*expect = TT_STRING | TT_PIPE | TT_APPEND | TT_OUT |
			TT_IN | TT_SEMICOLOM | TT_END;
		else if (meet(*expect, tok, TT_PIPE))
			*expect = TT_STRING;
		else if (meet(*expect, tok, TT_APPEND) || meet(*expect, tok, TT_OUT) ||
		meet(*expect, tok, TT_IN))
			*expect = TT_STRING;
		else if (meet(*expect, tok, TT_SEMICOLOM))
			*expect = TT_STRING | TT_IN | TT_OUT | TT_APPEND | TT_END;
		else if (meet(*expect, tok, TT_END))
			*expect = 0;
		else
		{
			validate_cond_bis(tok);
			return ;
		}
		idx++;
	}
}

/*
** la fonction validate prmet de verifier si notre ligne de commande est valide
** elle retourne 0 si la ligne de commande n'est pas valide
*/

int				validate(t_shell *glob, int *cmd_count)
{
	int			expect;
	int			index;

	index = 0;
	expect = TT_STRING | TT_APPEND | TT_IN | TT_OUT;
	validate_cond(index, glob, &expect, cmd_count);
	if (expect != 0)
	{
		return (0);
	}
	*cmd_count += 1;
	return (1);
}
