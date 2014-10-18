Sell Your Stuff  - Auction Site
(c) 2003 Harish JP/Priyananda Shenoy P
Distributed under GNU GPL 2.0

Contact:
harishjp@indiatimes.com
pshenoy_2000@yahoo.com

Requirements:
@ Linux ( may work on Win32 )
@ Apache 
@ MySQL
@ Perl 5.6+

To make it work:
@ copy entire public_html directory to some user's home directory
@ Change the Apache settings to allow user web pages - uncomment some lines 
	in /etc/httpd/conf/httpd.conf
@ change permissions of all cgi files to 755
	chmod 755 *.cgi
@ use auction.sql file to create tables
	mysql auction < auction.sql
@ change the username in public_html/common.pm ( $db_user )
@ use any browser to connect to HTTP Server like
	http://localhost/~user1/
	where user1 is the user whose home directory has public_html


