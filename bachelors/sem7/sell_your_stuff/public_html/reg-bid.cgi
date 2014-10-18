#! /usr/bin/perl
use common;

$lname = "";

sub put {
	$aucid = shift @_; 
	$price = shift @_;
	insert( "bid" ,  $aucid , $lname , $price );
	if( $db->err ){
		$db->do ( "update bid set value = ? where uname = ? and auctionid = ?" ,
				undef , $price , $lname , $aucid );
	}
	if( $db->err ){
		print "<h3>Error : could not enter bid</h3>" ;
		print "<hr width=100% />" ,  $conn->errstr ;
	}else{
		print "<h3>Bid sucessfully entered</h3> ";
	}
}
sub main(){
	$aucid = param('aucid' ); 
	$price = param('price' ); 
	put ( $aucid , $price );
}

init(1,1);
pagestart;
if( $lname = session_check() ){
	main();
}else{
	session_expired();
}
pageend;
cleanup;
