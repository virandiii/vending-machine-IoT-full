<?php

require 'koneksi.php';
ini_set('date.timezone', 'Asia/Jakarta');
$now = new DateTime();

$a = $_GET['a'];
$b = $_GET['b'];

$datenow = $now->format("Y-m-d H:i:s");
// mysqli_query($dbconnect, "INSERT INTO tb_topup VALUES ('','$card','$datenow')");

 $query = mysqli_query($dbconnect, "INSERT INTO topup VALUES ('','".$a."','".$b."','".$datenow."')");

//$result = mysqli_query($dbconnect, $sql);
 if ($query) {
     echo"berhasil";
 }else{
     echo"Gagal";
 }
	
?>