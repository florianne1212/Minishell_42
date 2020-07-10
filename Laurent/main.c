/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/10 11:12:33 by lcoiffie         ###   ########.fr       */
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
	char* s = "HOME";
	char *ret;
	int	rit;

	if (!(glob = malloc(sizeof(t_shell))))
		return (0);
	printf("\nargc %i", argc);
	printf("\nargv %s", argv[0]); //en attendant juste pour ne pas avoir d'erreurs de compilation
	fflush(stdout);
	sort_envp(envp, glob);
	if (!(ret = ft_getenv(glob->list_env, s)) && errno)
		perror("\ngetenv");
	printf("\nla valeur de %s est %s\n", s, ret);
	if((rit = ft_putenv(&glob->list_env, "MOI=toi")) == -1)
		perror("\nputenv");
	if((rit = ft_putenv(&glob->list_env, "MOItoi")) == -1)
		perror("\nputenv");
	if((rit = ft_putenv(&glob->list_env, "AENLEVER=cou==cou")) == -1)
		perror("\nputenv");
	if((rit = ft_putenv(&glob->list_env, "HOME=cou==cou")) == -1)
		perror("\nputenv");

	print_list(glob->list_env);
	printf("\n\n");
	if (!(ret = ft_getenv(glob->list_env, s)) && errno)
		perror("\ngetenv");
	printf("\nla valeur de %s est %s\n", s, ret);
	// //essai unset
	// ft_unsetenv(&glob->list_env, "COUCOU");
	// ft_unsetenv(&glob->list_env, "MOI");
	// ft_unsetenv(&glob->list_env, "AENLEVER");
	// print_list(glob->list_env);
	// //essai setenv
	// //modifie coucou, caca, coco et pas home
	// ft_setenv(&glob->list_env, "COUCOU","hello",1);
	//  ft_setenv(&glob->list_env, "CHOUCHOU","tresfort",1);
	// ft_setenv(&glob->list_env, "COCO","noix",0);
	// ft_setenv(&glob->list_env, "HOME","ben...home",1);
	// ft_setenv(&glob->list_env, "CHOUCHOU","encore plus fort",0);
	// printf("\n\n");
	// print_list(glob->list_env);



	printf("\n\n");
	clean_exit(glob);
	system("leaks a.out | grep 'leaked'");
	//system("leaks a.out");
}
