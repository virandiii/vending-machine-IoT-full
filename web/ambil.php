<?php

require 'koneksi.php';



if (isset($_GET['id'])) {
$id= $_GET['id'];
	


	$query = mysqli_query($dbconnect, "SELECT stok FROM tb_stok WHERE id = '$id' ");
  $cek =mysqli_num_rows($query);
  $data = mysqli_fetch_assoc($query);
  
  //mysqli_query($dbconnect, "SELECT stok FROM tb_stok WHERE id ='$id'");
  $status = $data ['stok'];

$output = 
    
      
        
            $status;
    $json = ($output);
    echo $json;

}