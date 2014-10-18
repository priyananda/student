#!/usr/bin/perl
use common;
init( 1,1);
pagestart;
session_end;
print <<QWERTY;
<script language='JavaScript'>
	function goHome(){
		window.top.location = "index.html" ;
	}
</script>
<h3> You have successfully logged out </h3><br />
<a href="javascript:goHome();" > Back to main page </a>

QWERTY
pageend;
cleanup;
