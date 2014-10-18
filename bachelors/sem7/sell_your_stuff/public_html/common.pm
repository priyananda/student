#!/usr/bin/perl

#	Authors: Harish.J.P and Priyananda Shenoy.P
#	Common routines required for Database and session management.

use DBI;
use CGI qw/:standard/;
use CGI::Util qw(rearrange make_attributes unescape escape expires);
use warnings;

$cgi = new CGI;
my $db_driver = "DBI:mysql:auction";
my $db_user = "harish";
my $db_password = "";
my $log_page = "error.log";
$req_db = 0;
$req_secure = 0;
$login_name = undef;
$cookie = undef;

#	Print the page header (title, stylesheet, javascript, banner)
sub pagestart{
print header( -cookie=>$cookie ) if($cookie);
print header unless($cookie);
print <<END_HTML_START;
<!DOCTYPE public "-//w3c//dtd html 4.01 transitional//en" 
		"http://www.w3.org/TR/html4/loose.dtd">
<HTML>
<HEAD>
	<TITLE>Sell Your Stuff 1.0</TITLE>
	<META NAME="Author" CONTENT="harish,shenoy">
	<META NAME="Keywords" CONTENT="harish,baba,bargain">
	<link href="images/main.css" rel=stylesheet >
	<script src="images/init.js" ></script>
</HEAD>

<body background="images/bg.gif" bgcolor="#FFFFFF" text="#000000" leftmargin="10" topmargin="10" >
END_HTML_START
}

#	Print the page footer (ads?, closehtml)
sub pageend{
print "</BODY></HTML>";
}

sub error{
	my $msg;
	$msg = join' ', "<br>Error:",@_, "<br>\n";
	print $msg;
	open LOG, ">>$log_page" or exit 0;
	print LOG "$msg\n";
	close LOG;
	exit 0;
}

#	Change to redirect to an error page and log the error for later use.
sub db_error{
	@error = @_;
	push @error, ": ". $db->errstr if($db and $db->err);
	error @error;
}

sub urlgen{
	my($page, $append, $i);
	$page = shift;
	$append = "";
	$append = shift(@_) . "=" . shift if($#_ != -1);
	$append .= "&$i=" . shift while( $i = shift);
	return ($append ne "") ? $page . "?" . $append : $page;
}

sub query{
	my $stat;
	$stat = $db->prepare(shift @_);
	$stat->execute(@_);
	return $stat;
}

# excute an insert on a table.
# insert <table-name> value list in order.
# returns no of rows inserted or the coressponding error.
sub insert{
	my $q = 'insert into ' . shift(@_) . ' values (?' . (',?' x $#_) . ')';
	return $db->do($q,undef,@_);
}

sub update{
	local( $query, %args, $_, @arr);
	$query = "update " . shift(@_) . " set ";
	%args = %{$_[0]};shift;
	push @arr ,"$i = " . $args{$i} for (keys(%args));
	$query .= join(",",@arr) . " where " . @_;
	return $db->do($query);
}

sub init_db{
	if($req_db){
		$db = DBI->connect($db_driver, $db_user, $db_password, {PrintError=>0})
			or db_error("DBError: connect $DBI::errstr" ) and return 0;
	}
	return 1;
}

sub genSessionId{
	my ($str,@arr) = ('','.','/','A'..'Z','a'..'z','0'..'9');
	$str .= $arr[rand 64] for(0..9);
	return $str;
}

#	Create a new session if
sub session_create{
	my($sid, $stat);
	$sid = genSessionId;
	$stat = $db->prepare("select uname from session where sid = ?");
	$sid = genSessionId while( $db->selectrow_array($stat, $sid) );
	$login_name = param("name");
	query("insert into session values( ?, ?, DATE_ADD(NOW(), INTERVAL 5 MINUTE) )",
			$sid, $login_name) or db_error("insertion failed");
	$cookie = cookie(-name=>'sid', -value=>$sid, -expires=>'+1h');
}

sub dirname {
	my ($dir) = @_;
	$dir =~ s/(.*\/)(.*)/$1/;
	return $dir;
}

# Send him to login.cgi with page parameter set properly.
sub session_expired{
#	print header( { -Location=>url("login.cgi","target",$cgi->page)} );
#	$location = "http://" . $ENV{'HTTP_HOST'} . ":".$ENV{'SERVER_PORT'}."/". $ENV{'REQUEST_URI'};
	$location = escape(self_url());
	$path = dirname( url(-full=>1) );
	
	print redirect $path."login.cgi?target=$location";
	exit(0);
}

# Check session validity.
sub session_check{
	return 1 unless($req_secure);
	query "delete from session where expires < NOW()";
	session_expired unless(defined cookie("sid"));
	$login_name = $db->selectrow_array(
			"select uname from session where sessionid = ?",undef,
			cookie("sid") ) or session_expired;
	$cookie = cookie(-name=>'sid', -value=>cookie('sid'), -expires=>'+1h') if($login_name);
	return $login_name;
}

# Terminate a session.
sub session_end{
	query "delete from session where sessionid = ?", cookie("sid");
	$req_secure = 0;
}

sub init{
	($req_db, $req_secure) = @_;
	return (init_db() == 1 and session_check());
}

sub cleanup{
	# update session expiry.
	query "update session set expires = DATE_ADD(NOW(), INTERVAL 5 MINUTE) where sessionid = ? ",
			cookie("sid") if($req_secure);
	# close connection
	$db->disconnect if(defined $db);
}

# Validate a form with the given rules
sub validate{
	my $pairs = $_[0];
	my %err;
	my $retval = 1;

	for( keys( %$pairs ) ){
		if(defined(param($_)) and param($_) =~ /$pairs->{$_}->[0]/){
			$err{$_} = ["", param($_) ];
		}else{
			$err{$_} = ["<td><font color='red'>" . $pairs->{$_}->[1] . "</font>", param($_) ];
			$retval = 0;
		}
	}
	return $retval, %err;
}

1;

__END__

dbh->selectrow_array
sth->rows
