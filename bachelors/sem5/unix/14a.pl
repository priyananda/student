#!/usr/bin/perl
while(chomp($_ = <>)){
	tr/\s+/\s/;
	$ass{$_}++ foreach (split (/\W/)) ;
}
print "$x : $y\n" while (($x,$y) = each %ass);

