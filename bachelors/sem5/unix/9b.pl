#!/usr/bin/perl
foreach ( @ARGV ){
	split(/ */);
	$dnum = $dnum * 2 + shift (@_) while(@_);
	print "$_ :: $dnum\n";
}
