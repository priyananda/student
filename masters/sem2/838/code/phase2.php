<html>
	<link rel=stylesheet href="../style.css" />
<?php
	include 'common.php';	
	print "Welcome <b>$username</b><br/>";
?>
	<script>
		var displayImages = new Array();
<?php
		print "cat1 = \"$cat1\";\n";
		print "cat2 = \"$cat2\";\n";
		
		for( $i = 0; $i < 20; $i++ ){
			$filen = getImage($phase2data,$i);
			print "displayImages[$i] = \"$filen\";\n";
		}
?>
		count = 20;
		function makeVisible(obj,val){
			if(val)
				obj.className = "";
			else
				obj.className = "invi";
		}
		function showImage(){
			if(count > 0){
				makeVisible(document.all.startbutton,false);
				makeVisible(document.all.mainimage,true);
				count--;
				document.all.mainimage.src = displayImages[count];
				document.all.imcount.innerHTML = "" + count;
				setTimeout('showImage()',5000);
			}else{
				makeVisible(document.all.mainimage,false);
				makeVisible(document.all.bsubmit,true);
			}
		}
	</script>

<center>
<b>Phase 2: Instructions</b><br />

You will be shown a series of images.<br />
Each image will be visible for 5 seconds. You don't need to do anything, just<br />
concentrate on the images.<br />

<br />
<b>Number of images left: <span id=imcount>20</span> </b>
<br />
<button id=startbutton onclick="showImage()" >Start</button>
<br />
<img src="" id=mainimage class=invi />
<br />

<form action=phase3.php method=post id=form1>
<?php
	putUserData();
	print "<input type=hidden name=imcount id=imcount value=\"15\"></input>";
?>
<input type=submit class=invi name=bsubmit id=bsubmit value="Click to start Phase 3"></input>
</form>

</center>
</html>
