<?php
	function Connection() {
		$dbHost   = "localhost";
		$dbUser   = "root";
		$dbPass   = "";
		$database = "log";
	   	
		$connection = mysql_connect($dbHost, $dbUser, $dbPass);

		if (!$connection) {
	    	die('MySQL ERROR: ' . mysql_error());
		}
		
		mysql_select_db($database) or die('MySQL ERROR: '. mysql_error());

		return $connection;
	}
?>
