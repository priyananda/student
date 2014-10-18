#!/usr/bin/perl
use common;

sub deleteAll{

}
sub processauc{
	local $aucid , $qs;
	$aucid = shift @_;
	$qs = query ( "select item.name from item,auction where auction.itemid = item.itemid and auction.auctionid =  ? and auction.end_date <= NOW() ", $aucid );
	while( @row = $qs->fetchrow_array() ){
		print "<h3>Congrats ::: You have topped the bid for item " , $row[0] , "    ";
		deleteAll;
	}
	$qs->finish;
}
init(1,1);
pagestart;
#sorry for the indentation 
if( $lname = session_check() ){ 
	print <<EOT;

<style>
	TD{ height=100px; }
</style>
<BODY background="images/bg.gif"  bgcolor="#FFFFFF" text="#000000" leftmargin="10" topmargin="10" > 
	<h3> Welcome <b> $lname </b> 
	<br /><hr width="100%" /><center>
<TABLE>
<TR>
	<TD><IMG SRC="images/browse.gif" WIDTH="48" HEIGHT="48" BORDER=0 ALT=""></TD>
	<TD colspan=5 > <a href='cat.cgi?catid=_all' >Browse Categories</a> </TD>
</TR>
<TR>
	<TD></TD>
	<TD><IMG SRC="images/user.gif" WIDTH="48" HEIGHT="48" BORDER=0 ALT=""></TD>
	<TD colspan=4> <a href='bid.cgi' >Bid for an Item</a></TD>
</TR>
<TR>
	<TD colspan=2></TD>
	<TD><IMG SRC="images/eyes.gif" WIDTH="48" HEIGHT="48" BORDER=0 ALT=""></TD>
	<TD colspan=3><a href='showbid.cgi' >View all my bids</a></TD>
</TR>
<TR>
	<TD colspan=3></TD>
	<TD><IMG SRC="images/add.gif" WIDTH="48" HEIGHT="48" BORDER=0 ALT=""></TD>
	<TD colspan=2><a href='itempage.cgi' >Add an auction</a></TD>
</TR>
</TABLE>

</center></body>
EOT
	$stat = query( "select uname,auctionid,max(value) from bid group by auctionid " ) ;
	while ( @row = $stat->fetchrow_array() ){
		processauc($row[1])  if( $row[0] eq $lname );
	}
}else{
	session_expired;
}
pageend;
cleanup;

