<?php
include_once 'koneksi.php';

?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.0/css/all.css'
        integrity='sha384-lZN37f5QGtY3VHgisS14W3ExzMWZxybE1SJSEsQp9S+oqd12jhcu+A56Ebc1zFSJ' crossorigin='anonymous'>
    <link rel="stylesheet" href="https://cdn.datatables.net/1.10.19/css/jquery.dataTables.min.css">
    <link rel="stylesheet" href="../css/bootstrap.min.css">
    <link rel="stylesheet" href="../css/blog-post.css">
    <script type="text/javascript" src="./js/Chart.min.js"></script>
    <script type="text/javascript" src="./js/Chart.js"></script>
    <title>Update Stok</title>
    <style>
        * {
            font-family: "Times New Roman", Times, serif;
        }

        table {
            border-collapse: collapse;
        }

        table,
        th,
        td {
            border: 1px solid black;
        }

        html {
            scroll-behavior: smooth;
        }

        div.dataTables_wrapper {
            width: 90%;
            margin: 0 auto;
        }

        .center-card {
            text-align: center;
            display: block;
            margin-top: 50px;
            margin-left: auto;
            margin-right: auto;
            width: 100%;
        }

        .tengah {
            text-align: center;
            display: block;
            margin-left: auto;
            margin-right: auto;
            width: 100%;
        }

        /* #chart-container {
            width: 90%;
            height: auto;
        } */

        .sudut {
            transform: rotate(270deg);
        }
    </style>
</head>

<body>
    <?php 
    ini_set('date.timezone', 'Asia/Singapore');
    $now = new DateTime();
    $datenow = $now->format("Y-m-d H:i:s");
    if (isset($_POST['submit'])) {
        $id = $_POST['id'];
        $stok = $_POST['stok'];  
        //var_dump($id,$stok);
        //die();
        $update = mysqli_query($conn,"UPDATE tb_stok SET stok = '$stok', date = '$datenow' WHERE id = '$id'");
        if ($update) {
            echo "<script type='text/javascript'>alert('Data Stok Berhasil Di Update');window.location.href='updatestokpetugas.php';</script>";
        }else {
            echo "<script type='text/javascript'>alert('Gagal !!');window.location.href='updatestok.php?id=$id';</script>";
        }
    }
   if(isset($_GET['id'])){
        $id = $_GET['id'];
        $select = mysqli_query($conn, "SELECT stok FROM tb_stok WHERE id = '$id'");
        $row = mysqli_fetch_assoc($select);
        $stok = $row['stok'];
        ?>
    <form action="tambah.php" method="post">
        <div class='container'>
            <div class="form-group">
                <label for="exampleInputEmail1">Stok</label>
                <input type="hidden" name="id" value="<?php echo $id ?>">
                <input type="number" class="form-control" name="stok" value="<?php echo $stok; ?>" id="exampleInputEmail1" aria-describedby="emailHelp"
                    placeholder="Enter Text">
            </div>
            <button type="submit" name="submit" class="btn btn-primary form-control">Submit</button>
        </div>

    </form>
    <?php }
   ?>
</body>
<script src="../js/jquery.min.js"></script>
<script src="../js/highcharts.js"></script>
<script src="../js/exporting.js"></script>
<script src="https://cdn.datatables.net/1.10.19/js/jquery.dataTables.min.js"></script>
<script type="text/javascript">
    $(document).ready(function () {
        $('#example').DataTable({
            "scrollY": 300,
            "scrollX": 100
        });
    });
</script>

</html>