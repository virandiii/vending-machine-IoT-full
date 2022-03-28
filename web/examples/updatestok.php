<?php 
include_once 'koneksi.php';


 ?>
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8" />
  <link rel="apple-touch-icon" sizes="76x76" href="../assets/img/logo.png">
  <link rel="icon" type="image/png" href="../assets/img/logo.png">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
  <title>
    Update Stok
  </title>
  <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0, shrink-to-fit=no' name='viewport' />
  <!--     Fonts and icons     -->
  <link href="https://fonts.googleapis.com/css?family=Montserrat:400,700,200" rel="stylesheet" />
  <link href="https://maxcdn.bootstrapcdn.com/font-awesome/latest/css/font-awesome.min.css" rel="stylesheet">
  <!-- CSS Files -->
  <link href="../assets/css/bootstrap.min.css" rel="stylesheet" />
  <link href="../assets/css/paper-dashboard.css?v=2.0.1" rel="stylesheet" />
  <!-- CSS Just for demo purpose, don't include it in your project -->
  <link href="../assets/demo/demo.css" rel="stylesheet" />
<!--batas-->
  <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.0/css/all.css'
        integrity='sha384-lZN37f5QGtY3VHgisS14W3ExzMWZxybE1SJSEsQp9S+oqd12jhcu+A56Ebc1zFSJ' crossorigin='anonymous'>
    <link rel="stylesheet" href="https://cdn.datatables.net/1.10.19/css/jquery.dataTables.min.css">
    <link rel="stylesheet" href="css/blog-post.css">
    <style>
        * 
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

<body class="">
  <div class="wrapper ">
    <div class="sidebar" data-color="white" data-active-color="danger">
      <div class="logo">
        <a class="simple-text logo-mini">
          <div class="logo-image-small">
            <img src="../assets/img/logo.png">
          </div>
          <!-- <p>CT</p> -->
        </a>
        <a class="simple-text logo-normal">
          vending iot
          <!-- <div class="logo-image-big">
            <img src="../assets/img/logo-big.png">
          </div> -->
        </a>
      </div>
      <div class="sidebar-wrapper">
        <ul class="nav">
          <li>
            <a href="./dashboard.php">
              <i class="nc-icon nc-bank"></i>
              <p>Dashboard</p>
            </a>
          </li>
          <li class="active ">
            <a href="./updatestok.php">
              <i class="nc-icon nc-single-copy-04"></i>
              <p>Stok</p>
            </a>
          </li>
          
          <li>
            <a href="./tables.php">
              <i class="nc-icon nc-tile-56"></i>
              <p>Transaction Table</p>
            </a>
          </li>
          <li>
            <a href="./saldo.php">
              <i class="nc-icon nc-tile-56"></i>
              <p>Topup Table</p>
            </a>
          </li>
        </ul>
      </div>
    </div>
    <div class="main-panel">
      <!-- Navbar -->

      <nav class="navbar navbar-expand-lg navbar-absolute fixed-top navbar-transparent">
        <div class="container-fluid">
          <div class="navbar-wrapper">
            <div class="navbar-toggle">
              <button type="button" class="navbar-toggler">
                <span class="navbar-toggler-bar bar1"></span>
                <span class="navbar-toggler-bar bar2"></span>
                <span class="navbar-toggler-bar bar3"></span>
              </button>
            </div>
            <a class="navbar-brand" href="javascript:;">Stok Admin</a>
          </div>
          <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navigation" aria-controls="navigation-index" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-bar navbar-kebab"></span>
            <span class="navbar-toggler-bar navbar-kebab"></span>
            <span class="navbar-toggler-bar navbar-kebab"></span>
          </button>
          <div class="collapse navbar-collapse justify-content-end" id="navigation">
            <form>
             
            <ul class="navbar-nav">
              <li class="nav-item btn-rotate dropdown">
                <a class="nav-link dropdown-toggle" href="http://example.com" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                  <i class="nc-icon nc-settings-gear-65"></i>
                  <p>
                    <span class="d-lg-none d-md-block">Some Actions</span>   
                  </p>
                </a>
                <div class="dropdown-menu dropdown-menu-right" aria-labelledby="navbarDropdownMenuLink">
                  <a class="dropdown-item" href="../logout.php">Logout</a>
                </div>
              </li>
              
            </ul>
          </div>
        </div>
      </nav>
      <div class="content">
        <div class="row">
          <div class="col-md-12">
            <div class="card">
              <div class="card-header">
              
    

    <h1 class="center-card">Stock Table </h1>
    <div class="dataTables_wrapper">
        <table id="example" class="table table-striped display nowrap" style="width:100%">
            <thead>
                <tr class="bg-dark text-white">
                    <td>NO</td>
                    <td>NAME</td>
                    <td>PRICE</td>
                    <td>STOCK</td>
                    <td>DATE</td>
                    
                </tr>
            </thead>
            <tbody>
                <?php
                $ven = mysqli_query($conn, "SELECT * FROM tb_stok");
                if (mysqli_num_rows($ven) > 0) {
                    $i = 1;
                    while ($a = mysqli_fetch_assoc($ven)) {
                ?>
                <tr>
                    <td><?php echo $i++; ?></td>
                    <td><?php echo $a['nama']; ?></td>
                    <td><?php echo $a['harga']; ?></td>
                    <td><?php echo $a['stok']; ?></td>
                    <td><?php echo $a['date']; ?></td>
                  
                <?php }
                } else {
                    echo "<tr> Data Tidak Ada </tr>";
                }
                ?>
            </tbody>

        </table>
    </div>
    <div class="card-header">
    <div class="card-header">
    

  <!--   Core JS Files   -->
  <script src="../assets/js/core/jquery.min.js"></script>
  <script src="../assets/js/core/popper.min.js"></script>
  <script src="../assets/js/core/bootstrap.min.js"></script>
  <script src="../assets/js/plugins/perfect-scrollbar.jquery.min.js"></script>
  <!--  Google Maps Plugin    -->
  <script src="https://maps.googleapis.com/maps/api/js?key=YOUR_KEY_HERE"></script>
  <!-- Chart JS -->
  <script src="../assets/js/plugins/chartjs.min.js"></script>
  <!--  Notifications Plugin    -->
  <script src="../assets/js/plugins/bootstrap-notify.js"></script>
  <!-- Control Center for Now Ui Dashboard: parallax effects, scripts for the example pages etc -->
  <script src="../assets/js/paper-dashboard.min.js?v=2.0.1" type="text/javascript"></script><!-- Paper Dashboard DEMO methods, don't include it in your project! -->
  <script src="../assets/demo/demo.js"></script>


  <script src="js/jquery.min.js"></script>
<script src="js/highcharts.js"></script>
<script src="js/exporting.js"></script>
<script src="https://cdn.datatables.net/1.10.19/js/jquery.dataTables.min.js"></script>
<script type="text/javascript">
    $(document).ready(function () {
        $('#example').DataTable({
            "scrollY": 300,
            "scrollX": 100
        });
    });
</script>
</body>

</html>