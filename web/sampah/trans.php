<?php
$kurang = 1;



if (isset($_POST['id'])) {
    include 'koneksih.php';
    $id = $_POST['id'];
    $query = mysqli_query($dbconnect, "SELECT * FROM rfid WHERE id ='$id'");
    $cek =mysqli_num_rows($query);
    if ($cek > 0){
        $data = mysqli_fetch_assoc($query);
        $hasil = $data['stok'] - $kurang ;
        //var_dump($id,$stok);
        //die();
        mysqli_query($dbconnect, "UPDATE rfid SET stok = '$hasil' WHERE id ='$id'");
        $status = "Transaksi Sukses";
    }else{
        $status = "gagal";
        $hasil_saldo = "-";
}
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
