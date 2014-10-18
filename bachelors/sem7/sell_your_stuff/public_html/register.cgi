#!/usr/bin/perl
use common;

init(1,0);

$vpassre = param("pass") or ".*";

%rules = (
	"lname"=>['.+', "Login name cannot be empty"],
	"pass"=>['.+', "Password cannot be empty"],
	"vpass"=>[$vpassre, "Passwords do not match"],
	"fname"=>['.+',"First name cannot be empty"],
	"sname"=>['.+',"Last name cannot be empty"],
	"address"=>['.+',"Address cannot be empty"],
	"city"=>['.+',"City cannot be empty"],
	"pincode"=>['[0-9]+',"Invalid Pincode"],
	"email"=>['^.+@.+[.].+$',"Email is invalid"],
	"occupation"=>['.+',"Occupation cannot be empty"],
	"address"=>['.+',"Address cannot be empty"],
	"ccno"=>['.+',"Credit card no cannot be empty"],
	"ccdate"=>['\d{4}-\d\d-\d\d',"Credit card date Invalid [yyyy-mm-dd]"]
);

pagestart;
($valid, %err) = validate(\%rules);

if( $valid != 0){
	if(insert("users", param("lname"), param("pass"), "0000-00-00",param("email"), param("ccno"),
			1000, 5, "0000-00-00",param("fname"), param("sname"), param("ccdate"),
			param("address"),param("city"),param("pincode"),param("occupation") )){
		print "You have been successfully registered.";
	}else{
		$err{'lname'}->[0] = "<td><font color='red'>Username already in use choose another";
#		db_error("insertion failed");
		$valid = 0;
	}
}

if($valid == 0){
print <<END_HTML_CODE
<form name="reg_form" action="register.cgi" >
<table  width="100%" border="1" cellspacing="5" cellpadding="5" align="center" bordercolor=#F5F5FF>
 <tr>
	<th colspan=3> Registration for membership </th>
 <tr>
	<td width="50%"> Login Name 
	<td><input name="lname" id="lname" size=20 value="$err{'lname'}->[1]">
	$err{"lname"}->[0]
 <tr>
	<td> Password
	<td><input type="password" name="pass" id="pass" size=20 >
	$err{"pass"}->[0]
 <tr>
	<td> Confirm Password
	<td><input name="vpass" type="password" id="vpass" size=20>
	$err{"vpass"}->[0]
 <tr>
	<th colspan=3>&nbsp; </th>
 <tr>
	<td> First name
	<td><input name="fname" id="fname" size=20 value="$err{'fname'}->[1]">
	$err{"fname"}->[0]
 <tr>
	<td> Surname
	<td><input name="sname" id="sname" size=20 value="$err{'sname'}->[1]">
	$err{"sname"}->[0]
 <tr>
	<td> Address
	<td><input name="address" id="address" size=20 value="$err{'address'}->[1]">
	$err{"address"}->[0]
 <tr>
	<td> City 
	<td><input name="city" id="city" size=20 value="$err{'city'}->[1]">
	$err{"city"}->[0]
 <tr>
	<td> PIN Code
	<td><input type="text" name="pincode" id="pincode" size=20 value="$err{'pincode'}->[1]">
	$err{"pincode"}->[0]
 <tr>
	<td> EMail ID
	<td><input name="email" id="email" size=20 value="$err{'email'}->[1]">
	$err{"email"}->[0]
 <tr>
	<th colspan=3> &nbsp; </th>
 <tr>
	<td> Occupation
	<td><input name="occupation" id="occupation" size=20 value="$err{'occupation'}->[1]">
	$err{"occupation"}->[0]
 <tr>
	<td> Yearly Income Range
	<td><select name="income" >
		<option name="poor" >Below 1 lakh</option>
		<option name="middle" >Between 1 and 2 Lakhs</option>
		<option name="upper" >Between 2 and 3 Lakhs</option>
		<option name="rich" >Above 3 Lakhs</option>
		</select>
 <tr>
	<td> Credit Card Number
	<td><input type="text" name="ccno" id="ccno" size=20 value="$err{'ccno'}->[1]">
	$err{"ccno"}->[0]
 <tr>
	<td> Credit Card Expiry date
	<td><input type="text" name="ccdate" id="ccdate" size=20 value="$err{'ccdate'}->[1]">
	$err{"ccdate"}->[0]
 <tr>
	<th colspan="2"> &nbsp; </th></tr>
 <tr>
	<td colspan=3> Please read the policy document
 <tr>
	<td colspan=3><center><iframe src="policy.html" scrolling="vertical" width="60%"></iframe></center>
 <tr>
	<td colspan=3 align="center"> <input type="submit" value="Register">
END_HTML_CODE
}
pageend;
cleanup;
