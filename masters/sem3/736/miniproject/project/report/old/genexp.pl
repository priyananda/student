#!/usr/bin/perl

sub gen_actual_window
{
	open FILE, ">actual_window.txt";
	my $actual = 1;
	for($t = 0 ; $t < 100; ++$t){
		$ideal = 100 if ($t <  30);
		$ideal = 16 if ($t >= 30 && $t < 60);
		$ideal = 150 if ($t >= 60);
		print FILE "$t $ideal $actual\n";
		if($actual < $ideal){
			if($actual <= 32){
				$actual = $actual * 2;
			}else{
				$actual += 5;
			}
		}
		$actual = $ideal if($actual > $ideal);
	}
	close FILE;
}

sub gen_ideal_calc
{
	open FILE, ">ideal_calc.txt";
	my $actual = 1;
	for($t = 1 ; $t < 100; ++$t){
		$rr = 0.0001;
		$cl = 100 - $t;
		$iw = ($cl / $rr) * 100;
		print FILE "$t $rr $cl $iw\n";
	}
	close FILE;
}

#gen_actual_window();
gen_ideal_calc();