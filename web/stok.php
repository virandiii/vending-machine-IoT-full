<?php
$kurang = 1;



if (isset($_POST['id'])) {
    include 'koneksi.php';
    $id = $_POST['id'];
    $query = mysqli_query($dbconnect, "SELECT * FROM tb_stok WHERE id ='$id'");
    $cek =mysqli_num_rows($query);
    $data = mysqli_fetch_assoc($query);
    if ($data['stok']<=0) {
        return false;
        }
        
        $hasil = $data['stok'] - $kurang ;
        //var_dump($id,$stok);
        //die();
        mysqli_query($dbconnect, "UPDATE tb_stok SET stok = '$hasil' WHERE id ='$id'");
        $status = "Transaksi Sukses";
    
       
 
$output = 
    [
        "Detail" =>
        [
            "Status" => $status,
        ]
    ];
    $json = json_encode($output);
    echo $json;
}
