/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 09:19:16 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/18 00:42:39 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cherche si la fonction est l'un de nos homemade builtin et l'execute le cas
** echeant
*/
int		check_and_run_builtin(t_shell *glob, char **arg)
{
	int	ret;

	ret = -1;
	if (!(ft_strcmp(arg[0], "cd")))
		ret = builtin_cd(glob, glob->fd,arg);
	else if (!(ft_strcmp(arg[0], "echo")))
		ret = builtin_cd(glob, glob->fd,arg);
	else if (!(ft_strcmp(arg[0], "env")))
		ret = builtin_cd(glob, glob->fd,arg);
	else if (!(ft_strcmp(arg[0], "export")))
		ret = builtin_cd(glob, glob->fd,arg);
	else if (!(ft_strcmp(arg[0], "pwd")))
		ret = builtin_cd(glob, glob->fd,arg);
	else if (!(ft_strcmp(arg[0], "unset")))
		ret = builtin_cd(glob, glob->fd,arg);
	return (ret);
}

char 	*ft_search_env_path(t_shell glob, char *command)
{
	(void)glob;
	return (command);
}

int		no_command_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	errno = ENOENT;
	return (1);
}

void	ft_change_case_instruction(char *instruction)
{
	int	i;

	i = 0;
	while (instruction[i])
	{
		if (instruction[i] > 64 && instruction[i] < 91)
			instruction[i] += 32;
		i++;
	}
}

/*
** recherche si builtin, recherche si chemin absolu ou relatif,
** puis recherche dans PATH
**-il faut que la liste chainee variables d'environnement ai ete initialisees (sort_envp)
**-la commande est passee en tant que tableau de strings de la forme :
** "commande" "arg0" "arg1" ... "NULL"
//-pour l'instant sortie dans glob->fd, a revoir +++
*/
int		ft_run_simple_command(t_shell *glob, char **command_arg)
{
	int		ret;
	char	*path;

	path = NULL;
	ret = 0;
	ft_change_case_instruction(command_arg[0]);
	if ((ret = check_and_run_builtin(glob, command_arg)) >= 0)
		return (ret);
	if (command_arg[0][0]== '/')
		if (!(path = ft_strdup(command_arg[0])))
			return (errno_return_int(ENOMEM, 1));
	else if (command_arg[0][0]== '.')
	{
		if (!(path = change_rel_to_abs(command_arg[0])))
			return (errno_return_int(ENOMEM, 1));
	}
	else
	{
		if (!(path = ft_search_env_path))
			return (no_command_found(command_arg[0]));
	}
	return (ret);
	//creer tableau env
	//lancement commande (path, arg, env), retour = retour de la commancde
}

	//passer arg[0] en minuscules (sont insensibles a la casse ces connes de commandes) DONE
	//chercher si builtin et run builtin DONE
	// chercher si path absolu (commence par /) DONE
	//chercher si path relatif (commence par .) DONE
	//chercher dans PATH si commande existe
	//retourner une erreur si aucun processus ok DONE
	//creer le tableau env
	//lancer la commande avec fork et xecve
	int main()
	{
		char *lolo;
		lolo = ft_strdup("LololO234");
		ft_change_case_instruction(lolo);
		ft_putstr('\n');
		ft_putstr(lolo);
		return (0);

	}