/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:59:31 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/25 00:51:49 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**-------create process)-------
** create new process with protections
** je ne l'utilise pas, enzo le trouve dangeureux ( le fork dans boucle)
*/

pid_t	create_process(void)
{
	pid_t pid;

	errno = 0;
	pid = fork();
	while (pid == -1 && errno == EAGAIN)
		pid = fork();
	return (pid);
}

/*
** fonction qui capte le signal et efface ce qui apparait sur le terminal
** n est le numero du signal, a envoyer a $? + 128
*/

void	control_child(int n)
{
	exit(128 + n);
}

/*
** taches a accomplir par child
** execution de la commande, passer la sortie dans le tube de sortie
** recuperer l'entree dans tube d'entreemettre pour $? le retour de execve
*/

int	child_process(t_shell *glob, char *path, char **arg, char **env)
{
	int	ret;

	ret = 0;
	// signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, control_child);
	signal(SIGQUIT, control_child);
	ret = execve(path, arg, env);
	//global_retour = ret;
	(void)glob;
	return(ret);
}


void control_C_parent(int n)
{
	ft_putstr_fd("\n", 2);
	global_retour = 128 + n;
}

void control_back_parent(int n)
{
	ft_putstr_fd("Quitter (core dumped)\n", 2);
	global_retour = 128 + n;
}
/*
** taches a accomplir par le pere
** pipe entrees sortie vers child
*/

void	father_process(int child_pid)
{
	int	status;
	signal(SIGINT, control_C_parent);
	signal(SIGQUIT, control_back_parent);

	waitpid(child_pid, &status, 0);
}

/*
** comme son nom l'indique fait un fork puis execute la commande dans le fils
*/

int		fork_and_run_cmd(t_shell *glob, char *path, int i, char **env)
{
	pid_t pid;

	pid = fork();
	glob->cmd[i].pid = pid;
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if(child_process(glob, path, glob->cmd[i].cmd_arg, env) < 0)
			return (1);
	}
		//attention a le proteger
	else
	{
		father_process(pid);
	}
	return (0);
}
