<?php
ini_set('date.timezone', 'Asia/Singapore');
include 'koneksi.php';    


if (isset($_POST['id'])) {    
    $id = $_POST['id'];
    $query = mysqli_query($dbconnect, "SELECT * FROM tb_stok WHERE id ='$id'");
    $cek = mysqli_num_rows($query);
    if ($cek > 0){
        $now = new DateTime();
        $jumlah = 1;
        $data = mysqli_fetch_assoc($query);
        $idmakanan = $data['id'];
        $nama = $data['nama'];               
        $bulan = $now->format("m");
        $tahun = $now->format("Y");     
        $query = mysqli_query($dbconnect, "SELECT * FROM tb_penjualan WHERE id_makanan ='$id' AND YEAR(tanggal) = $tahun AND MONTH(tanggal) = $bulan");
        $data = mysqli_fetch_assoc($query);  
        $terjual = $jumlah + $data['jumlah']; 
        if (mysqli_num_rows($query) == 0) {
            $insert = mysqli_query($dbconnect, "INSERT INTO tb_penjualan (id_makanan, nama, jumlah, tanggal) VALUES ('$id', '$nama', '$jumlah', NOW())");
            if ($insert) {
                $output = ["Status" => 'Berhasil Insert !!'];
                $json = json_encode($output);
                echo $json;
            }
        }else {
            $update = mysqli_query($dbconnect, "UPDATE tb_penjualan SET jumlah = $terjual WHERE id_makanan ='$id' AND YEAR(tanggal) = $tahun AND MONTH(tanggal) = $bulan");
            if ($update) {            
                $output = ["Status" => 'Berhasil Update !!'];
                $json = json_encode($output);
                echo $json;
            }
        }                      
    }else{
        $status = "gagal";
        $hasil_saldo = "-";
    }
}
