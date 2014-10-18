#!/usr/bin/perl
use common;
init(1,1);
pagestart;

sub workIt{
	$aucid = param("aucid");
	$want = param( "accept");
	if( $want eq "yes" ){
		print "<h3> The auction goes to you !!! </h3>";
		$stat = query( "select itemid from auction where auctionid = ? " , $aucid);
		$itemid = $stat->fetchrow_array();
		$db->do ( "delete from auction where auctionid = ? " , undef , $aucid );
		$db->do ( "delete from item where itemid = ? " , $itemid );
		$db->do ( "delete from bid here auctionid = ?" , $aucid );
		
	}else{
		print "<h3> Ypu cancelled the auction </h3>";
		$db->do ( "delete from bid where auctionid = ? and uname= ? " , $aucid , $lname );
	}
}
if( $lname = session_check() ){
	workIt;
}else{
	session_expired;
}
pageend;
cleanup;
