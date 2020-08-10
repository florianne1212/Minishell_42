/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/14 19:32:25 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		clean_exit(t_shell *glob)
{
	t_list_env *ptr;
	int i;

	i = 0;
	while (glob->list_env != NULL)
	{
		ptr = glob->list_env->next;
		free(glob->list_env->name);
		glob->list_env->name = NULL;
		free(glob->list_env->value);
		glob->list_env->value = NULL;
		free(glob->list_env);
		glob->list_env = ptr;
	}
	glob->list_env = NULL;
	//free(glob);
	glob = NULL;
	//env_destroy_array(glob->envirron);
}

int	empty_line(char *line)
{
	char *tmp;
	int i;

	i = 0;
	tmp = ft_strtrim(line, " \t");
	if (ft_strlen(tmp) != 0)
		i = 1;
	free(tmp);
	return(i);
}

/*void		init_glob(t_shell	*glob)
{

}*/


int			main(int argc, char **argv, char **envp)
{
t_shell	glob;
	char	*line;
	int		i;

	i = 1;
	signal(SIGINT, control_c); //permet d'intercepter le signal envoyer par ctrl-C
	signal(SIGQUIT, control_back); //permet d'intercepter le signal envoyer par ctrl-backslash
	ft_memset(&glob, 0, sizeof(t_shell));
	printf("\nargc %i", argc);
	printf("\nargv %s\n", argv[0]); //en attendant juste pour ne pas avoir d'erreurs de compilation
	fflush(stdout);
	sort_envp(envp, &glob);
	while (i == 1)
	{
		ft_putstr("$>");
		get_next_line(1, &line);
		//line = ft_strdup("ls");
		if (empty_line(line) != 0)
			lex_and_parse(line, &glob);
		if (strncmp(line, "exit", 4) == 0)
		{
			i = 0;
		}
		else
			free(line);
	}
	free(line);
	clean_exit(&glob);
}
