<?php
   include("dbconnect.php");
   	
   $link = Connection();

	$distance     = $_GET["distance"];
	$led_status   = $_GET["led_status"];
   $relay_status = $_GET["relay_status"];
	
   $query = "INSERT INTO `tbl_distance` (distance, led_status, relay_status) 
		VALUES ('".$distance."', '".$led_status."', '".$relay_status."')"; 
   	
   mysql_query($query, $link);
	     
   mysql_close($link);

   header("Location: index.php");
?>
