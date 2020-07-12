#include "minishell.h"

int main(int argc, char *argv[])
{
	(void)argc;
	printf("le nom est : %s\nla valeur est: %s\n", find_name(argv[1]), find_value(argv[1]));
	return (0);
}