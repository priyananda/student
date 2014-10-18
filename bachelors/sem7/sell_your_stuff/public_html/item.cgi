#! /usr/bin/perl
use common;

$item_id = 0;

sub dispItem{
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

sub getItem(){
	$stat = query ( "select * from item where itemid = ?" , $item_id) ;
	@row = $stat->fetchrow_array();
	dispItem @row;
	print "<br /><h3> Do you want to get this item for dirt cheap prices ?Then register now!!</h3><br />";
}
sub main(){
	init(1,0);
	pagestart;
	$item_id = param('itemid');
	getItem();
	pageend;
}
main();
