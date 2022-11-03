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