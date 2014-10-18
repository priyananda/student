#! /usr/bin/perl
use common;

$cgi = new CGI;

sub dispItem{
	print "<tr>\n";
	print "<td background='/images/th-bg.gif' > " ;
	print "<a href='biditem.cgi?itemid=" . shift(@_) . "'>" .  shift(@_) . "</a>\n" ;
	print  "<td bgcolor='orange'>" , shift (@_) , "\n";
	print "\n<td bgcolor='gold' align='center' >" , shift(@_);
}

sub showItems
{
	local $stat, $cnt;
	$stat = query( "select * from item order by cname");
	print "<table border='outer' width='100%' >\n" ;
	print "<tr><th>Name<th>Category<th>Description\n";
	while( @row = $stat->fetchrow_array ){
		dispItem @row ;
	}
	print "</table>\n";
}

sub main(){
	init(1,1);
	pagestart;
	autoEscape(undef);
	if( $lname = session_check ){
		showItems;
	}else{
		session_expired;
	}
	pageend;
	cleanup;
}
main();
