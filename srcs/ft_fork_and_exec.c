/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:59:31 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/21 10:44:10 by lcoiffie         ###   ########.fr       */
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

void	got_the_blody_signal(int n)
{
	n = 0;
	signal(SIGQUIT, got_the_blody_signal);
	signal(SIGINT, got_the_blody_signal);
	ft_putstr_fd("\b\b  \b\b", 1);
}

/*
** taches a accomplir par child
** execution de la commande, passer la sortie dans le tube de sortie
** recuperer l'entree dans tube d'entreemettre pour $? le retour de execve
*/

void	child_process(t_shell *glob, char *path, char **arg, char **env)
{
	int	ret;

	// signal(SIGQUIT, SIG_DFL);
	// signal(SIGINT, SIG_DFL);
	ret = execve(path, arg, env);
	glob->retour = ret;
}

/*
** taches a accomplir par le pere
** pipe entrees sortie vers child
** signaux ?
*/

void	father_process(int child_pid)
{
	int	status;

	waitpid(child_pid, &status, 0);
	//printf ("on est revenu dans le pere, youpi\n");
}

/*
** comme son nom l'indique fait un fork puis execute la commande dans le fils
*/

int		fork_and_run_cmd(t_shell *glob, char *path, int i, char **env)
{
	pid_t pid;

	// signal(SIGQUIT, got_the_blody_signal);
	// signal(SIGINT, got_the_blody_signal);
	pid = fork();
	glob->cmd[i].pid = pid;
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_process(glob, path, glob->cmd[i].cmd_arg, env);
	else
	{
		father_process(pid);
	}
	return (0);
}
