<?php

require 'koneksi.php';
ini_set('date.timezone', 'Asia/Jakarta');
$now = new DateTime();

$id = $_GET['id'];
$stok = $_GET['stok'];

$datenow = $now->format("Y-m-d H:i:s");
// mysqli_query($dbconnect, "INSERT INTO tb_topup VALUES ('','$card','$datenow')");

$update = mysqli_query($dbconnect,"UPDATE tb_stok SET stok = '$stok', date = '$datenow' WHERE id = '$id'");
        if ($update) {
            echo "Berhasil Update";
        }else {
            echo "gagal";
        }

//$result = mysqli_query($dbconnect, $sql);
 
	
?>