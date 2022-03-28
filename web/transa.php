<?php
ini_set('date.timezone', 'Asia/Singapore');
$now = new DateTime();

if (isset($_POST['id'])) {
    include 'koneksi.php';
    $datenow = $now->format("Y-m-d H:i:s");
    $id = $_POST['id'];
    $query = mysqli_query($dbconnect, "SELECT * FROM tb_stok WHERE id ='$id'");
    $cek =mysqli_num_rows($query);
    if ($cek > 0){
        $data = mysqli_fetch_assoc($query);
        $nama = $data['nama'];
        $harga = $data['harga'];
        //var_dump($id,$stok);
        //die();
        mysqli_query($dbconnect, "INSERT INTO transaksi VALUES ('','$nama', '$harga','$datenow')");
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

//$sql = "INSERT INTO transaksi VALUES ('','$datenow', '$tb_stok', '$value')";