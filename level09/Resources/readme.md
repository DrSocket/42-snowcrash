## level09

Files in home. an exec and a token file.

When I run the exec `./level09 token` it outputs:
> tpmhr

I try `./level09 1111`
> 1234

So every next character increases by 1.
`ltrace ./level09`
outputs:
> `You should not try to reverse this`, so I reverse it. Every next character decreses by 1 in script.c

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
	}

	int	main(int ac, char **av) {

		if (ac == 2)
			fn_sub(av[1]);
		write(1, "\n", 1);
		return (0);
	}

> gcc script.c -o decrypt

	level09@SnowCrash:~$ ./decrypt `cat token`
	f3iji1ju5yuevaus41q1afiuq

	level09@SnowCrash:~$ su flag09
	Password:
	Don't forget to launch getflag !
	flag09@SnowCrash:~$ getflag
	Check flag.Here is your token : `s5cAJpM8ev6XHw998pRWG728z`
