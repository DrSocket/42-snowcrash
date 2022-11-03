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