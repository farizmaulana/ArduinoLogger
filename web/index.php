<!DOCTYPE html>
<html>
	<head>
		<title>Distance Monitoring System</title>
		<meta charset="utf-8">
		<meta http-equiv="refresh" content="5">
		<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
		<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
		<link rel="stylesheet" type="text/css" href="css/dataTables.bootstrap.css">
		<link rel="stylesheet" type="text/css" href="css/dataTables.responsive.css">
		<link rel="stylesheet" type="text/css" href="css/index.css">
		<script type="text/javascript" language="javascript" src="js/jquery.min.js"></script>
		<script type="text/javascript" language="javascript" src="js/jquery.dataTables.min.js"></script>
		<script type="text/javascript" language="javascript" src="js/dataTables.responsive.min.js"></script>
		<script type="text/javascript" language="javascript" src="js/dataTables.bootstrap.js"></script>
		<script type="text/javascript" language="javascript" src="js/index.js"></script>
	</head>
	<body>
		<div class="container">
			<div class="header text-center">
				<h2>Distance Monitoring System</h2>
				<h2>Data Logging</h2>
			</div>
			<div class="row">
				<div class="col-md-10 col-md-offset-1">
					<table id="distance_table" class="table table-hover table-striped table-bordered dt-responsive" cellspacing="0" width="100%">
						<thead>
							<tr class="info">
								<th class="text-center">Log ID</th>
								<th class="text-center">Distance</th>
								<th class="text-center">LED Status</th>
								<th class="text-center">Relay Status</th>
								<th class="text-center">Time</th>
							</tr>
						</thead>
						<tbody>
							<?php
								include 'dbconnect.php';

								$link = Connection();
								$result = mysql_query("SELECT * FROM `tbl_distance` ORDER BY `id` DESC");
								
								if ($result != FALSE) {
									while ($row = mysql_fetch_array($result))
									{
										echo '<tr>';
										echo '<td class="text-center">' . $row['id'] . '</td>';
										echo '<td class="text-center">' . $row['distance'] . ' cm'.'</td>';
										echo '<td class="text-center">' . $row['led_status'] . '</td>';
										echo '<td class="text-center">' . $row['relay_status'] . '</td>';
										echo '<td class="text-center">' . $row['time'] . '</td>';
										echo '</tr>';
									}
									mysql_free_result($result);
	     							mysql_close();
								}
							?>
						</tbody>
					</table>
				</div>
			</div>
		</div>
	</body>
</html>
