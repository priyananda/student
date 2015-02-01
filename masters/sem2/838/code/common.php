<?php
	$dbh = 0;
	function connect(){
		global $dbh;
		$dbh = pg_connect("host=postgres.cs.wisc.edu dbname=priyananda_cs838 port=5432") or die('connection failed');
	}
	function query($str){
		global $dbh;
		$result = pg_query($dbh, $str) or die("query failed");
		return $result;
	}
	function execute($str){
		global $dbh;
		if(pg_exec($dbh, $str) == false){
			print "<font color=red><b>Statement execution failed:" . pg_errormessage() . "</b></font><br />";
		}
	}
	function disconnect(){
		global $dbh;
		pg_close($dbh);
	}
	function category1Name($type){
	    switch($type){
	    	case "1": return "Ninja";
	    	case "2": return "Democrat";
	    	case "3": return "Boy Band";
	    	case "4": return "Hufflepuff";
	    	case "5": return "Alien";
	    }
	}
	function category2Name($type){
	    switch($type){
	    	case 1: return "Pirate";
	    	case 2: return "Republican";
	    	case 3: return "Metal head";
	    	case 4: return "Ravenclaw";
	    	case 5: return "Predator";
	    }
	}
	function insertUser($username,$cat){
		connect();
 		execute("INSERT INTO user_data(user_name,category) VALUES ('$username','$cat')");
 		$result = query("SELECT MAX(user_id) FROM user_data");
 		$row = pg_fetch_row($result);
 		$userid = $row[0];
	 	disconnect();
	 	return $userid;
	}
	function putUserData(){
		global $username,$userid,$cat1,$cat2;
		print "<input type=hidden name=username id=username value=\"$username\"></input>";
		print "<input type=hidden name=userid id=userid value=\"$userid\"></input>";
		print "<input type=hidden name=cat1 id=cat1 value=\"$cat1\"></input>";
		print "<input type=hidden name=cat2 id=cat2 value=\"$cat2\"></input>";
	}
	function insertSelection($dataArr,$count,$catid,$priming){
		global $userid;
		
		$row = $dataArr[$count];
		$sp  = $row[0];
		$cp  = $row[1];
		
		connect();
		execute("INSERT INTO user_selection values('$userid','$cp','$sp','$catid','$priming')");
		disconnect();
	}
	function getImage($arr, $count){
		$row = $arr[$count];
		$sp  = $row[0];
		$cp  = $row[1];
		return 'images/image_' . $sp . '_' . $cp . '.png';
	}
	
	$username = $_REQUEST['username'];
	$userid   = $_REQUEST['userid'];
	$cat1     = $_REQUEST['cat1'];
	$cat2     = $_REQUEST['cat2'];
	
	$phase1data = array(
		array( 40, 10 ),
		array( 45, 0  ),
		array( 64, 90 ),
		array( 95, 50 ),
		array( 81, 20 ),
		array( 67, 10 ),
		array( 82, 60 ),
		array( 47, 50 ),
		array( 41, 50 ),
		array( 26, 10 ),
		array( 77, 90 ),
		array( 42, 30 ),
		array( 71, 30 ),
		array( 67, 60 ),
		array( 24, 80 )
	);
	$phase2data = array(
		array( 46, 30 ),
		array( 46, 30 ),
		array( 41, 20 ),
		array( 59, 60 ),
		array( 67, 70 ),
		array( 69, 80 ),
		array( 65, 70 ),
		array( 39, 20 ),
		array( 47, 30 ),
		array( 71, 80 ),
		array( 46, 30 ),
		array( 38, 20 ),
		array( 63, 70 ),
		array( 68, 80 ),
		array( 63, 70 ),
		array( 42, 20 ),
		array( 61, 60 ),
		array( 74, 90 ),
		array( 46, 30 ),
		array( 36, 10 )
	);
	$phase3data = array(
		array( 96, 20 ),
		array( 72, 50 ),
		array( 42, 90 ),
		array( 38, 80 ),
		array( 21, 20 ),
		array( 74, 70 ),
		array( 41, 50 ),
		array( 32, 70 ),
		array( 21, 70 ),
		array( 54, 10 ),
		array( 84, 30 ),
		array( 48, 80 ),
		array( 24, 90 ),
		array( 53, 30 ),
		array( 65, 50 )
	);
?>
