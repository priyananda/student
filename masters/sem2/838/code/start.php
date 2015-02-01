<html>
	<link rel=stylesheet href="../style.css" />
<center>
<?php
	include 'common.php';
	
	$cat  = $_REQUEST['category'];
	$cat1 = category1Name($cat);
    $cat2 = category2Name($cat);
	
	$userid = insertUser($username,$cat);

 	print "Welcome <b>$username</b> !<br />";
 	print "You will be shown a series of images. Each image is either a <b>$cat1</b> or a <b>$cat2</b>. ";
 	print "You have to classify the image into one of the two categories.<br/>";
 	print "For example, this is what a <b>$cat1</b> looks like:<br />";
?>
<img src="images/image_30_0.png"><br />
<?php
    print "And this is what a <b>$cat2</b> looks like:<br />";
?>
<img src="images/image_80_100.png"><br />
Note that all objects in the same category don't look the same. Given an image,
you need to decide what category it is closer to.<br />
<br />
This experiment has three phases. Please follow the instructions of each phase.
The complete experiment should last no more than 7 minutes.<br /> Remember that there
are no right or wrong answers.<br />
<br />
<form action="phase1.php" method=post>
<?php
	putUserData();
	print "<input type=hidden name=imcount id=imcount value=\"15\"></input>";
?>
	<input type=submit value="Click to start Phase 1"></input>
</form>

</center>
</html>
