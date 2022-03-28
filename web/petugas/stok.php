<?php
$kurang = 1;

if(isset($_POST['no'])){
    include 'koneksi.php';
    $id = $POST['id'];
    $query = mysqli_query($conn, "SELECT * FROM tb_stok WHERE no ='$id'");
    $cek =mysqli_num_rows($query);
    if ($cek > 0){
        $data = mysqli_fecth_assoc($query);
        $hasil = $data['stok'] - $kurang;
        var_dump($id,$stok);
        die();
        mysqli_query($conn, "UPDATE tb_stok SET stok = '$hasil' WHERE `no` ='$id'");
        
    }else{
    
}
}

?>