/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/05 01:28:51 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int retour;

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
		if(glob->list_env->value != NULL)
			free(glob->list_env->value);
		glob->list_env->value = NULL;
		free(glob->list_env);
		glob->list_env = ptr;
	}
	//env_destroy_array(glob->envirron);
	glob->list_env = NULL;
	//free(glob);
	glob = NULL;

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
	char	*line;
	int i;
	t_shell glob;

	retour = 0;
	ft_memset(&glob, 0, sizeof(t_shell));
	//global_retour = 0;
	glob.running = 1;
	sort_envp(envp, &glob);
	while (glob.running)
	{
		manage_control(&glob);
		ft_putstr_fd("$>", 2);
		//get_next_line(0, &line);
		gnl2(0, &line);
		//line = ft_strdup("ls");
		if (empty_line(line) != 0)
			lex_and_parse(line, &glob);
		// printf("line = %s\n", line);
		free(line);
	}
	i = glob.exit_code;
	clean_exit(&glob);
	(void)argv;
	(void)argc;
	return (i);
}
