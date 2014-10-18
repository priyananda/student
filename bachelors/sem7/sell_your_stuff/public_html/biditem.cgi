#! /usr/bin/perl
use common;

$item_id 	= "";
$auction_id = "";

sub dispItem{
	print "<h3>Item Details</h3><br />";
	print "<table width='100%' >\n";
	shift @_;
	
	print "<tr background='/images/th-bg.gif' > " ;
	print "<td>Name:\n" ;
	print "<td>" , shift(@_) , "\n";
	
	print "<tr bgcolor='orange'> " ;
	print "<td>Category:\n" ;
	print "<td>" , shift(@_) , "\n";


	print "<tr bgcolor='gold'> " ;
	print "<td>Description:\n" ;
	print "<td>" , shift(@_) , "\n";

	print "</table>";
}
sub dispBids{
	local $auc_id;
	$auction_id = shift @_;
	$stat = query ( "select * from bid where auctionid = ? order by value desc" , $auction_id );
	
	print "<hr width=100% >\n" ;
	print "<h3><b>All the Bids</b></h3>\n" ;
	print "<table width='100%' >\n";
	print "<tr><th>User<th>Value\n" ;
	while ( @row = $stat->fetchrow_array ){
		print "<tr bgcolor='orange'>\n";
		print "<td > $row[1]\n";
		print "<td > $row[2]\n";
	}
	print "</table>";
}
sub dispAuction{
	local @arr;
	@arr = @_;
	
	print "<hr width=100% >\n" ;
	print "<h3><b>Auction Details</b></h3>\n" ;
	print "<table width='100%' >\n";
	
	print "<tr bgcolor='gold'> " ;
	print "<td>Owner:\n" ;
	print "<td>" , $arr[1] , "\n";

	
	print "<tr bgcolor='gold'> " ;
	print "<td>Start Date:\n" ;
	print "<td>" , $arr[2] , "\n";

	print "<tr bgcolor='gold'> " ;
	print "<td>End Date:\n" ;
	print "<td>" , $arr[3] , "\n";


	print "<tr bgcolor='gold'> " ;
	print "<td>INumber of Items:\n" ;
	print "<td>" , $arr[4] , "\n";


	print "<tr bgcolor='gold'> " ;
	print "<td>Starting Price:\n" ;
	print "<td>" , $arr[7] , "\n";

	print "</table>";

	dispBids $arr[0];
}
sub getBid{
	print "<table border=1> ";
	print "<tr>";
	print " <th colspan=2 bgcolor=gold >Bid for this Item :</th>";
	print "<tr bgcolor=#c4f745 >";
	print " <td>Bidding Price: </td>";
	print " <form action='reg-bid.cgi' method=get >";
	print " <td><input type=text size=10 name=price >";
	print "   <input type=hidden name='aucid' value='$auction_id' ></input>";
	print "<tr bgcolor=#c4f745 >";
	print " <td colspan=2 align=center><input type='submit' value='Bid' >";
	print "</form></table>";
}
sub getItem(){
	$stat = query ( "select * from item where itemid = ?" , $item_id);
	@row = $stat->fetchrow_array();
	dispItem @row;
	
	$stat = query ( "select * from auction where itemid = ?" , $item_id);
	@row = $stat->fetchrow_array();
	dispAuction @row;
	
	getBid ;

	$stat->finish;
}
sub main(){
	init(1,1);
	pagestart;
	$item_id = param('itemid');
	$lname = param('name');
	getItem();
	pageend;
	cleanup;
}
main();
