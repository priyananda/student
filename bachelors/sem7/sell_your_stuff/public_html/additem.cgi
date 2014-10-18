#! /usr/bin/perl
use common;
$lname = "";


sub addItem{
	insert "item" ,
			"NULL" , shift (@_) , shift(@_) , shift(@_) ;
	$stat = query "select max(itemid) from item" ;
	$iid = $stat->fetchrow_array;
	$stat->finish;
	$db->do ( "insert into auction values ( NULL , ? , NOW() , ? , ? , ? , ? , ? )" , undef,
			$lname , shift(@_) , shift(@_) ,
			$iid , shift(@_) , shift(@_) );
}

sub func{
	$itemname =  param( 'itemname' );
	$itemcat  =  param( 'itemcat' );
	$itemdesc =  param( 'itemdesc' );
	
	$aucend  =  param( 'aucend' );
	$aucnum =  param( 'aucnum' );
	$aucdesc =  param( 'aucdesc' );
	$aucval =  param( 'aucval' );
	
	%rules = (
		itemname => [ '.+', 'Item name cannot be empty' ],
		itemcat => [ '.+', 'Item Category cannot be empty' ],
		itemdesc => [ '.+', 'Item descrition cannot be empty' ],
		aucend => [ '\d{4}-\d{2}-\d{2}', 'Invalid date' ],
		aucnum => [ '\d+', 'Item Number cannot be empty' ],
		aucdesc => [ '.+', 'Item Description cannot be empty' ],
		aucval => [ '\d+', 'Value cannot be empty' ],
	);
	($valid, %err) = validate(\%rules);
	if($valid){
		addItem ( 	$itemname , $itemcat , $itemdesc,
				$aucend, $aucnum ,
				$aucdesc, $aucval 
		);
		if( $db->err ){
			print"<h3>Error:" , $db->errstr , "</h3>" ;
		}else{
			print "<h3>Item Successfully Added</h3><br />" ; 
		}
	}else{
		print "<h2>Error!!</h2><br><hr wdith='100%'>";
		print "<h3> You have left some fields empty </h3><br>";
		print $err{'itemname'}->[0],'<br>';
		print $err{'itemcat'}->[0],'<br>';
		print $err{'itemdesc'}->[0],'<br>';
		print $err{'aucend'}->[0],'<br>';
		print $err{'aucnum'}->[0],'<br>';
		print $err{'aucdesc'}->[0],'<br>';
		print $err{'aucval'}->[0],'<br>';
		print "<a href='javascript:history.back(-1);' >Back</a>" ;
	}
}
sub main(){
	init(1,1);
	pagestart;
	autoEscape( undef );
		
	$lname = session_check();
	if( $lname ){
		func;
	}else{
		session_expired;
	}
	pageend;
	cleanup;
}
main();
