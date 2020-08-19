
#include "../includes/minishell.h"

int check_exit_arg(t_shell *glob, char **arg)
{
	int i;

	i = 0;
	if (arg[1][0] == '-')
			i++;
	while(arg[1][i])
	{
		if (arg[1][i] < '0' || arg[1][i] > '9')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": argument numerique necessaire\n", 2);
			glob->exit_code = 2;
			glob->running = 0;
			return (1);
		}
		i++;
	}
	if (arg[2])
	{
		ft_putstr_fd("exit: trop d'arguments\n", 2);
		return (1);
	}
	return (0);
}

int builtin_exit(t_shell *glob, int fd, char **arg)
{
	(void)fd;
    if (arg[1])
	{
		if (check_exit_arg(glob, arg))
			return (1);
		glob->exit_code = (unsigned char)ft_atoi(arg[1]);
		glob->running = 0;
		return (0);
	}
	glob->exit_code = 0;
    glob->running = 0;
    return (0);
}
// teste si valeur numerique  si pas valeur numerique : exit avec code 2 et messqge erreur str: argument numerique necessaire
// si valeur numerique et autre argument : ne sort pas et exit: trop d'arguments