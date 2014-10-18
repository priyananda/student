#!/usr/bin/perl

use common;
init(1,1);
pagestart;
if( $lname = session_check() ){
	print "session , $lname ";
}else{
	print "No session";
}
pageend;
cleanup;
