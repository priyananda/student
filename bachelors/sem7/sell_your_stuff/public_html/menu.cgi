#!/usr/bin/perl
use common;

init(1,1);

pagestart;
print <<EOT;
<style>
.menu {
	text-indent:0.1in;
	background:#ebffe6;
//	padding:2px;
	border-color:#ebffe6;
	border-style:solid;
	border-width:1px;
	cursor:hand;
}
</style>
<script>
function menu_over( m){
	m.style.background = "#c5f4b9";
	m.style.borderColor = "#333333";
}

function menu_out( m ){
	m.style.background = "#ebffe6";
	m.style.borderColor = "#ebffe6";
}

function menu_clicked( url ){
	window.top.main_frame.location = url;
}

function addMenu( name, url ){
	var str = "<tr><td align=center> <img src='images/bullet.gif' width=30>";
	str += "<td class='menu'"  ;
	str +=  " onmouseover='menu_over(this)'" ;
	str +=  " onmouseout='menu_out(this)'"   ;
	str +=  " onclick='menu_clicked("        ;
	str += '"' 	;
	str += url	;
	str += '"'	;
	str += ")' >" ;
	str += name;
	document.writeln( str );
}

function beginMenu(){
	document.writeln("<TABLE STYLE='background:#ebffe6;border:groove;' CELLPADDING=0  CELLSPACING=1 ALIGN='CENTER'>");
}

function endMenu(){
	document.writeln("</table>");
}

beginMenu();
addMenu('User Page', 'home.cgi'  );
addMenu('Change Account Info', 'chacct.cgi' );
addMenu('Log out', 'logout.cgi' );
endMenu();
</script>
EOT
pageend;
