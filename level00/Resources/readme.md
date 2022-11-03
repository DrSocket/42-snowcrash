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