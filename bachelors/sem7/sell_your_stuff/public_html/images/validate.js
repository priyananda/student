var elements = new Array(
	"lname", "pass" , "vpass",
	"fname", "sname" , "address",
	"city", "pincode" , "email" ,
	"occupation", "ccno" , "ccdate"
);

function doBadThing(name , val){
	if( val )
		document.getElementById( name ).src = "images/sn.gif";
	else
		document.getElementById( name ).src = "images/sy.gif";
	return ! val ;
}
function checkAll(){
	ret = true;
	for (i = 0 ; i < elements.length ; i++ ){
		elem = document.getElementById (elements[i]);
		ret = doBadThing( elements[i] + "_image" , elem.value == "" );
	}
	if( document.all.pass == "" || document.all.pass.value != document.all.vpass.value )
		ret = doBadThing( "vpass_image" , 1 );
	return ret;
}

