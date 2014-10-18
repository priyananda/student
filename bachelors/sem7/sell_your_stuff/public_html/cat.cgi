#! /usr/bin/perl
use common;

$cat_id = 0;

sub dispItem{
	print "<tr>\n";
	print "<td background='/images/th-bg.gif' > " ;
	print "<a href='item.cgi?itemid=" . shift(@_) . "'>" .  shift(@_) . "</a>\n" ;
	shift @_;
	print "\n<td bgcolor='gold' align='center' >" , shift(@_);
}

sub dispCat{
	print "<tr>\n";
	print "<td> <img src='/images/folder.gif' />\n";
	print "<td background='/images/th-bg.gif' > " ;
	$x = shift(@_);
	print "<a href='cat.cgi?catid=" .$x  . "'>" . $x  . "</a>\n" ;
	print "\n<td bgcolor='gold' align='center'>" , shift(@_); 
}
sub showCategory
{
	local $stat, $cnt;
	$stat = query ( "select * from item where cname=?" , $cat_id );
	print "<table border='outer' width='100%' >\n" ;
	print "<tr><th>Name<th>Description\n";
	while( @row = $stat->fetchrow_array ){
		dispItem @row ;
	}
	print "</table>\n";
}
sub showAll
{
	local $stat;
	$stat = query ( "select * from category" );
	print "<table border='outer' width='100%' >\n" ;
	print "<tr><th> <th>Name<th>Description\n";
	while( @row = $stat->fetchrow_array ){
		dispCat @row;
	}
	print "</table>\n";
	
}
sub main(){
	init (1,0);
	pagestart;
	$cat_id = param('catid');
	if( $cat_id eq "_all" ){
		showAll;
	}else{
		showCategory;
	}
	pageend;
	cleanup;
}
main();
