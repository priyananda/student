#! /usr/bin/perl
use common;

$lname = "";

sub getPass
{
	$q = query ( "select password from users where name = ? " , $lname );
	$val = $q->fetchrow_array();
	return $val;
}

sub updatePass
{
	local $new_pass;
	$new_pass = param( 'newpass' );
	if( $new_pass ){
		$db->do ( "update users set password=? where name=?" , undef , $new_pass , $lname );
		print "<h3>Password successfully updated</h3>";
	}else{
		print "<h3>Some fields are empty</h3>";
		formPage;
	}
}
sub formPage
{
	print <<OINK;
	<table border=0 >
	<form method='POST' action='chacct.cgi' >
	<tr>
	 <th colspan=2> Change your password 
	<tr>
	 <td>Old Password
	 <td><input type=password size=10 name=oldpass>
	<tr>
	 <td>New Password
	 <td><input type=password size=10 name=newpass>
	<tr>
	 <td><input type=submit value=Change >
	</table></form> 
OINK
}
sub yesLog{
	$old_pass = param('oldpass');
	$crr_pass = getPass() ;
	if ($old_pass eq $crr_pass) {
		updatePass;
	}else{
		formPage;	
	}
}
sub main(){
	init(1,1);
	pagestart;
	if( $lname = session_check() ){
		yesLog;
	}else{
		session_expired;
	}
	pageend;
	cleanup;
}
main();
