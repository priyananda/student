@sumOfValues = (0);
@catOfValues = (0);
@names = (0);

$count = 0;
$numfiles = 0;

($whatfiles) = @ARGV;

for $file(`ls results/$whatfiles*.txt`){
	++$numfiles;
	open FILE, "<$file";
	$count = 0;
	while(<FILE>){
		chomp;
		($a,$b) = split(/ /);
		$names[$count] = $a;
		$sumOfValues[$count] = $sumOfValues[$count] + $b;
		$catOfValues[$count] = $catOfValues[$count] . " " . $b;
		++$count;
	}
	close FILE;
}

open AVGFILE, ">results/${whatfiles}_average.txt";
open COLFILE, ">results/${whatfiles}_collated.txt";

for($i = 0 ; $i < $count; ++$i ){
	print AVGFILE "" . $names[$i] . " " . ( $sumOfValues[$i] * 1.0 / $numfiles ) . "\n";
	print COLFILE "" . $names[$i] . " " . $catOfValues[$i] . "\n";
}

close AVGFILE;
close COLFILE;
