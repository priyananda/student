#!/usr/bin/perl
use common;

init(1,0);
pagestart;

print <<HSTFH;

<table align=center width='100%'>
 <form action="additem.cgi" method=GET >
 <tr>
 	<th colspan=2> Item Information
 <tr>
 	<td> Item Name
	<td> <input size=20 name='itemname' >
 <tr>
 	<td> Description
	<td> <input size=20 name='itemdesc' > 
 <tr>
 	<td> Category
	<td> <select name='itemcat' >
HSTFH

$stat = query "select name from category" ;
while( @row = $stat->fetchrow_array ){
	$x = $row[0];
	print "<option value='$x' > $x </option>";
}
$stat->finish;
print "</select>";

print<<ASDF;
 <tr>
	<th colspan=2> Auction Information
 <tr>
 	<td> Auction End date
	<td> <input size=20 name='aucend' >
 <tr>
 	<td> Item Count
	<td> <input size=20 name='aucnum' >
 <tr>
 	<td> Auction Description
	<td> <input size=20 name='aucdesc' >
 <tr>
 	<td> Starting Value
	<td> <input size=20 name='aucval' >
 <tr>
 	<td><input type=submit value=Submit >
 </form>
 <form action='addcat.cgi' method=GET>
 <tr>
 	<th colspan=2> Add a category 
 <tr>
 	<td> Category Name 
	<td> <input type=text name='catname' >
 <tr>
 	<td> Category Description 
	<td> <input type=text name='catdesc' >
 <tr>
 	<td><input type=submit value=Submit >
 </table>
 </form>
ASDF
pageend();
cleanup();
