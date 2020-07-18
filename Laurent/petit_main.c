#include "minishell.h"

void autre(char **arg)
{
	int i = 0;

	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
}


int	main(int argc, char *argv[])
{
	autre(&argv[1]);
	(void)argc;
	return (0);
}
