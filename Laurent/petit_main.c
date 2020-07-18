#include "minishell.h"

int	main()
{
	struct stat bufferstat;

	int ret;

	ret = 0;
	ret = stat("/Users/laurentcoiffier/Desktop/minishell/florianne/Laurent/a.out", &bufferstat);
	printf("le fichier existe, le retour est %d\n", ret);
	if (S_ISREG(bufferstat.st_mode))
			printf("c'est bien un fichier regulier\n");

	ret = stat("/Users/laurentcoiffier/Desktop/minishell/florianne/Laurent", &bufferstat);
	printf("le fichier n'existe pas, le retour est %d\n", ret);
	if (S_ISREG(bufferstat.st_mode))
			printf("c'est bien un fichier regulier\n");
	ret = stat("/bin/LS", &bufferstat);
	printf("le fichier ls existe, le retour est %d\n", ret);
	if (S_ISREG(bufferstat.st_mode))
			printf("c'est bien un fichier regulier\n");
	return(0);
}