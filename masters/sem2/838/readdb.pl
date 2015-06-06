#!/s/std/bin/perl

use DBI;
use CSL::Pg;

$dbh = DBI->connect("dbi:Pg:dbname=priyananda_cs838;host=postgres.cs.wisc.edu;port=5432")
	or die "Couldn't connect to database: " . DBI->errstr;

$usr_stmt = $dbh->prepare("select user_id,user_name from user_data order by user_id");
$sel_stmt = $dbh->prepare("select color,shape,priming,choice from user_selection where user_id = ?");

$usr_stmt->execute();
$usr_stmt->bind_columns(\$user_id,\$user_name);

while($usr_stmt->fetch()){
	$sel_stmt->execute($user_id);
	$sel_stmt->bind_columns(\$color,\$shape,\$priming,\$choice);
	
	$filename     = $user_name . $user_id . ".txt";
	$linefilename = $user_name . $user_id . ".line";
	
	open(FILEHANDLE, ">data/$filename");
	
	while($sel_stmt->fetch()){
		print FILEHANDLE "$priming $shape $color $choice\n";
	}
	
	close(FILEHANDLE);
	
	`echo > "data/$linefilename"`;
}
