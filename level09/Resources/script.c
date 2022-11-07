#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	fn_sub(char *str) {
	char *new;
	int i;
	new = malloc(sizeof(char) * strlen(str) + 1);

	for (i = 0; i < strlen(str); i++)
		new[i] = str[i] - i;
	printf("%s\n", new);
	free(new);
	new = 0;
}

int	main(int ac, char **av) {

	if (ac == 2)
		fn_sub(av[1]);
	write(1, "\n", 1);
	return (0);
}