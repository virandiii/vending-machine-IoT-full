<?php

require 'koneksi.php';



  $query = mysqli_query($dbconnect, "SELECT nama , stok FROM tb_stok ");
  $cek =mysqli_num_rows($query);
  $data = mysqli_fetch_assoc($query);
  $data2 = mysqli_fetch_assoc($query);
  $data3 = mysqli_fetch_assoc($query);
  
  //mysqli_query($dbconnect, "SELECT stok FROM tb_stok WHERE id ='$id'");
  $status = $data ['nama'];
  $status2 = $data ['stok'];

  $status3 = $data2 ['nama'];
  $status4 = $data2 ['stok'];

  $status5 = $data3 ['nama'];
  $status6 = $data3 ['stok'];


$output = 
[
    "Detail" =>
    [
        "Name" => $status,
        "Stock" => $status2,
    ]
    
];

$json = json_encode($output);
echo $json;

$output2 = 
[
    
        "Name" => $status3,
        "Stock" => $status4,
    
    
];


    

$json = json_encode($output2);
echo $json;

$output3 = 
[
    
        "Name" => $status5,
        "Stock" => $status6,
    
    
];


    

$json = json_encode($output3);
echo $json;
