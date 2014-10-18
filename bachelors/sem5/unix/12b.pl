#!/usr/bin/perl
chomp ($_ = <>);
@arr1 = split /\W/ ;
chomp ($_ = <> );
@arr2 = split /\W/ ;
@comp = sort @arr1,@arr2;
$hash{lc $_} = ":: only in line one" foreach ( @arr1 );
foreach ( @arr2 ){
	if ( $hash{lc $_} ){
		$hash{lc $_} = "::in both lines"
	}else{
		$hash{lc $_} = "::only in line two"
	}
}
print "\n---------------------output-------------------\n";
foreach (@comp){
	if ( $x = $hash{lc $_}){print "$_ $x\n";$hash{lc $_}="";}
}
