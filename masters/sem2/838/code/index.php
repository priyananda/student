<html>
	<link rel=stylesheet href="../style.css" />
	<script>
	function uncheck(thebox){
	  thebox.checked = true;
	}
	function submitt(theForm){
	  if( theForm.username.value == "" || theForm.username.value == null ){
	    theForm.username.focus();
	    alert("Please enter a name");
	    return false;
	  }
	  return true;
	}
	</script>
	<center>
		<b>CS 838 Computational Cognitive Science Final Project</b><br /><br />
		Priyananda Shenoy<br />
		shenoy@cs.wisc.edu<br /><br />
		
		<font color=red><b>
		This experiment is closed. You may still take part in the experiment,<br />
		but your data will not be considered. Thank you very much for visiting.<br />
		</b></font>
		<br />
		
		Thanks for taking part in my experiment. Please enter your name in the
		box shown below:<br />
		<form method="POST" action="start.php" onsubmit="return submitt(this)" >
			Name: <input name="username" id="username" type=text width=30 /><br /><br />
			
			What follows is a classification experiment, where you will be given<br />
			objects and asked to classify them into two categories. To make it<br />
			fun, you can choose the names of the categories:<br /><br />
			
			<select name="category">
				<option value=1>Ninjas vs Pirates</option>
				<option value=2>Democrats vs Republicans</option>
				<option value=3>Boy Bands vs Metal heads</option>
				<option value=4>Hufflepuffs vs Ravenclaws</option>
				<option value=5>Aliens vs Predators</option>
			</select>
			<br /><br />
			<input type=checkbox checked onClick="uncheck(this)"> I agree to all terms and conditions</input>
			<br /><br />
			<input type=submit value=Start></input>
		</form>
	</center>
</html>
