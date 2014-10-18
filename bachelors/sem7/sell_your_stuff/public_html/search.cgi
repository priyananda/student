#!/usr/bin/perl

use common;
init(1,0);
pagestart;
$keyword = param('keyword');
if ( $keyword eq "" ){
	print "<h3> Type Something !!!!<h3>";
	print "<a href='search.html' >Back to Search</a>";
	pageend;
	cleanup;
	exit;
}
$cnt = 0;
print "<hr width=100% >";
print <<DONG;
<center><img src="images/see.gif" ></center>
<span style='background-image:url("images/th-bg.gif")' ><h3>Search results for $keyword in Items </h3></span>
DONG
$stat = query ( 
	"select name , cname, description from item where name LIKE '\%$keyword\%'" .
	" or description LIKE '\%$keyword\%' " );
while( @row = $stat->fetchrow_array() ){
	print "<div style='background-color:white;'> ";

	print "<b>Item:</b> " ; $_ = $row[0];
	s/$keyword/<b><font color=blue >$&<\/font><\/b>/gi;
	print "$_<br>\n" ;
	
	print "<b>Category:</b> " ; $_ = $row[1];
	s/$keyword/<b><font color=blue>$&<\/font><\/b>/gi;
	print "$_<br>\n" ;

	print "<b>Description:</b> " ; $_ = $row[2];
	s/$keyword/<b><font color=blue>$&<\/font><\/b><\/span>/gi;
	print "$_<br>\n" ;
	
	print "</div><br><br>";
	$cnt++;
}
print <<DONG;
<br><br>
<span style='background-image:url("images/th-bg.gif")' ><h3>Search results for $keyword in Categories </h3></span>
DONG
$stat->finish;

$stat = query ( 
	"select name ,description from category where name LIKE '\%$keyword\%'" .
	" or description LIKE '\%$keyword\%' " );

while( @row = $stat->fetchrow_array() ){
	print "<div style='background-color:white;'> ";

	print "<b>Category:</b> " ; $_ = $row[0];
	s/$keyword/<b><font color=blue>$&<\/font><\/b>/gi;
	print "$_<br>\n" ;

	print "<b>Description:</b> " ; $_ = $row[1];
	s/$keyword/<b><font color=blue>$&<\/font><\/b><\/span>/gi;
	print "$_<br>\n" ;
	
	print "</div><br><br>";
	$cnt++;
}
print "<h3> $cnt results found </h3>";
pageend;
cleanup;
