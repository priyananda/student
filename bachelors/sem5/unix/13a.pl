#!/usr/bin/perl
chomp($_ = <>);
tr /a-zA-Z0-9//cd;
$_ = lc;
$rev = reverse;
if ( $_ eq $rev ){
	print "Palindrome\n";
}else{
	print "Not a Palindrome\n";
}	
