for $f(`ls example/flread*.txt`)
{
	chomp($f);
	open RD, "<$f";
	$f =~ s/read/write/;
	open WR, "<$f";
	
	$rdsum = $rcnt = $wsum = $wcnt = 0;

	while(<RD>){
		chomp;
		$rdsum += $_;
		$rcnt++;
	}

	$rv = ( $rdsum / $rcnt );
	printf "read avg: $rv \n";

	while(<WR>){
		chomp;
		$wsum += $_;
		$wcnt++;
	}

	$wv = ( $wsum / $wcnt );
	printf "write avg: $wv\n";

	print "$f : ratio: " . ($wv/$rv) . "\n";

	close RD;
	close WR;
}