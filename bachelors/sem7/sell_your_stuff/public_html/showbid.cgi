#! /usr/bin/perl
use common;

$lname = 0;

sub dispAuction{
	print "<tr background='images/th-bg.gif' > " ;
	print "<td>" , shift(@_) , "\n";
	shift @_;
	print "<td>" , shift(@_) , "\n";
	print "<td>" , shift(@_) , "\n";
	print "<td>" , shift(@_) , "\n";
	print "<td><a href='item.cgi?itemid=" ,  shift(@_) , "' >See It</a>\n";
	print "<td>" , shift(@_) , "\n";
	print "<td>" , shift(@_) , "\n";
}

sub getItem(){
	print "<h3>All your auctions</h3><br/><hr width='100%'/>";
	$stat = query( "select * from auction where owner = ?" , $lname );
	print "<table width='100%' >\n";
	print "<tr><th>Auction ID<th>Start Date<th>End Date<th> Num Item <th>Item <th>Description<th>Value";
	while(@row = $stat->fetchrow_array() ){
		dispAuction (@row);
	}
	print "</table>";
	print "<hr width=100%><h3>All your bids</h3><br/><hr width='100%'/>";

	
	$stat = query(
		"select auction.auctionid , value  from bid , auction where bid.uname = ? and bid.auctionid = auction.auctionid ",
		$lname
	);
	print "<table width='100%' >\n";
	print "<tr><th> Auction ID <th>Value";
	while(@row = $stat->fetchrow_array() ){
		print "<tr bgcolor='#e0daad' > " ;
		print "<td>" , shift(@row) , "\n";
		print "<td>" , shift(@row) , "\n";
	}
	print "</table";
	
}
sub main(){
	init(1,1);
	pagestart;
	if( $lname = session_check() ){
		print "<h3> Bid information for $lname</h3><br /> ";
		getItem;
	}else{
		session_expired;
	}
	pageend;
	cleanup;
}
main();
