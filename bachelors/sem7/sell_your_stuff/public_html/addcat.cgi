#! /usr/bin/perl
use common;
$lname = "";


sub addCat{
	insert "category" ,
			shift (@_) , shift(@_);
}

sub main(){
	init(1,1);
	pagestart;
	autoEscape( undef );
	
	$lname = $login_name;
	%rules = (
		catname=>['.+',"Category name should not be blank"],
		catdesc=>['.+',"Category Description should not be blank"],
	);
	($valid, %err) = validate(\%rules);

	if($valid){	
		$catname =  param( 'catname' );
		$catdesc =  param( 'catdesc' );
		addCat ( $catname , $catdesc);
		if( $db->err ){
			print"<h3>Error:" , $db->errstr , "</h3>" ;
		}else{
			print "<h3>Category Successfully Added</h3><br />" ; 
		}
	}else{
		print "<h2>Error!!</h2><br><hr wdith='100%'>";
		print $err{'catname'}->[0], "<br>";
		print $err{'catdesc'}->[0], "<br>";
		print "<h3> You have left some fields empty </h3><br>";
		print "<a href='javascript:history.back(-1);' >Back</a>" ;
	}
	pageend;
	cleanup;
}
main();
