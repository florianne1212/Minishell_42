/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 11:37:56 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/17 12:50:20 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		clean_exit(t_shell *glob)
{
	while (glob->list_env != NULL)
	{
		free(glob->list_env->name);
		free(glob->list_env->value);
		free(glob->list_env);
		glob->list_env = glob->list_env->next;
	}
	free(glob);
}

int			main(int argc, char **argv, char **envp)
{
	t_shell	*glob;

	// char* s = "HOME";
	// char *ret;
	// int	rit;
	// char *arg[] = {"echo", "nu=", "chouchou", "chou=bidou", "classe", NULL};
	// char *arg2[] = {"env", NULL};
	//char *arg3[] = {"export","LOLO=gouzi", "LALA=gouza", NULL};


	if (!(glob = malloc(sizeof(t_shell))))
		return (0);
	(void)argc;
	(void)argv;
	//printf("\nargc %i", argc);
	//printf("\nargv %s", argv[0]); //en attendant juste pour ne pas avoir d'erreurs de compilation
	//printf("\nargv %s", argv[1]); //en attendant juste pour ne pas avoir d'erreurs de compilation

	fflush(stdout);
	sort_envp(envp, glob);
	glob->envirron = NULL;

	//clean_exit(glob);
	system("leaks a.out | grep 'leaked'");
	// system("leaks a.out");
}