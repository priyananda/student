#!/usr/bin/perl

use common;
init(0,0);
pagestart;

print "<h3><font color='blue'>Thank you for your opinion </h3>";
$val = param( 'poll_opt' );
print "<hr width='100%' >";
print "We think you are $val too !!! ";

pageend;
cleanup;
