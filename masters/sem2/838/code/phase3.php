<html>
	<link rel=stylesheet href="../style.css" />
<?php
	include 'common.php';
	
	$count    = $_REQUEST['imcount'];
	$bsubmit  = $_REQUEST['submit'];
	
	print "Welcome <b>$username</b><br/>";
	
	if($count != 15){
		$catid = 1;
		if($bsubmit == $cat2)
			$catid = 2;
		insertSelection($phase3data,$count,$catid,1);
	}
?>
<center>
<b>Phase 3: Instructions</b><br />

You will be shown a series of images. You need to classify them as either<br />
a <?php print "$cat1"; ?> or a <?php print "$cat2"; ?>. Concentrate and<br />
click on what you think is the best answer.<br />
<br />
<b>Number of images left: <?php print $count; ?></b>
<br />

<?php
	if($count == 0)
		print "<form action=end.php method=post>";
	else
		print "<form action=phase3.php method=post>";
	
	putUserData();

	if($count != 0){
		$count--;
		$which = getImage($phase3data,$count);
		print "<br /><img src=\"$which\" /><br /><br />";
		print "<input type=hidden name=imcount id=imcount value=\"$count\"></input>";
		print "<input type=submit name=submit value=\"$cat1\"></input>";
		print "<input type=submit name=submit value=\"$cat2\"></input>";
	}else{
		print "<br/><br/><input type=submit name=submit value=\"Done\"></input>";
	}
?>
</form>

</center>
</html>
