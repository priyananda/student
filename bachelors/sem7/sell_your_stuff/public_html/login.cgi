#!/usr/bin/perl

use common;

init(1,0);

%rules = (
	'name'=>['.+', "Login name cannot be empty"],
	'password'=>['.+', "Password cannot be empty"]
);


($valid, %err) = validate(\%rules);
if($valid){
	$pass = $db->selectrow_array("select password from users where name = ? ",
					undef, param(name) );
	if($pass and $pass eq param("password") ){
		session_create;
	}else{
		$valid = 0;
	}
}

pagestart;
unless($valid){
print <<EOT;
<h2>You are here because of one of the following:</h2><br>
<ul>
<li>Your login name or password is incorrect.[Enter correct info]
<li>Your session has expired.[Re-Login]
<li>You have disabled cookies in your browser. [Enable cookies]
<li>Your browser does not support cookies. [Get another browser]
</ul>
<form action="login.cgi" method=POST target="main_frame">
<table width='100%' cellpadding=0 cellspacing=1 border=0>
	<tr>
	<td>Name
	<td><input size=10 name='name' />
	$err{'name'}->[0]
	<tr>
	<td>Password
	<td><input size=10 type=password name='password' />
	$err{'password'}->[0]
	<tr>
	<td>
	<td><input type=submit value="  Go  " onsubmit="check(name)"/>
</table>
</form>
EOT
}else{
	print<<EOT;
Welcome $login_name to our site.
<script>
<!--
	window.top.location = 'home.html';
// -->
</script>
You should be automatically redirected to Home, else
<a href='home.html' target="_parent">Click Here</a>
EOT
}

pageend;
cleanup;
