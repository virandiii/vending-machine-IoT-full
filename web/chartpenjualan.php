<?php
$koneksi    = mysqli_connect("localhost", "root", "", "ven");
$label1 = ["Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"];
 
for($bulan = 1;$bulan < 13;$bulan++)
{
	$query = mysqli_query($koneksi,"select jumlah as terjual from tb_penjualan where id_makanan ='1' AND MONTH (tanggal)='$bulan'");
	$row = $query->fetch_array();
    $jumlah_produk[] = $row['terjual'];  //$data = mysqli_fetch_assoc($query);

    $query = mysqli_query($koneksi,"select jumlah as terjual from tb_penjualan where id_makanan ='2' AND MONTH (tanggal)='$bulan'");
	$row = $query->fetch_array();
    $jumlah_produk2[] = $row['terjual'];
    
    $query = mysqli_query($koneksi,"select jumlah as terjual from tb_penjualan where id_makanan ='3' AND MONTH (tanggal)='$bulan'");
	$row = $query->fetch_array();
	$jumlah_produk3[] = $row['terjual'];

}



?>
<!DOCTYPE html>
<html>
<head>
	<script type="text/javascript" src="js/Chart.js"></script>
</head>
<body>
<div class="container">
		<canvas id="myChart"width="100" height="45"></canvas>
	</div>
 
 
	<script type="text/javascript">
		var ctx = document.getElementById("myChart").getContext('2d');
		var myChart = new Chart(ctx, {
			
			type: 'line',
			data: { 
				labels: <?php  echo json_encode($label1); ?>,
				datasets: [{
					label: 'Twister',
					fill: false,
                    lineTension: 0.2,
                   backgroundColor: "rgba(59, 100, 222, 1)",
                   borderColor: "rgba(59, 100, 222, 1)",
                    pointHoverBackgroundColor: "rgba(59, 100, 222, 1)",
						        pointHoverBorderColor: "rgba(59, 100, 222, 1)",
					data: <?php echo json_encode($jumlah_produk); ?>,
					borderWidth: 1
                    

					
				},
              {
                label: 'Lays',
					fill: false,
                    lineTension: 0.2,
                    backgroundColor: "rgba(34, 139, 35, 0.9)",
                    borderColor: "rgba(34, 139, 35, 0.9)",
                    pointHoverBackgroundColor: "rgba(34, 139, 35, 0.9)",
						        pointHoverBorderColor: "rgba(34, 139, 35, 0.9)",
					data: <?php echo json_encode($jumlah_produk2); ?>,
					borderWidth: 1
                
                },
                {
                    label: 'Soba',
					fill: false,
                    lineTension: 0.2,
                    backgroundColor: "rgba(201, 29, 29, 1)",
                    borderColor: "rgba(201, 29, 29, 1)",
                    pointHoverBackgroundColor: "rgba(201, 29, 29, 1)",
						        pointHoverBorderColor: "rgba(201, 29, 29, 1)",
					data: <?php echo json_encode($jumlah_produk3); ?>,
					borderWidth: 1
                }]
			},
			options: {
				scales: {
					yAxes: [{
						gridLines: {
    	                              color: "211, 211, 211",
    	                          }

					
					}],
          
				}
			}
		});


    
	</script>
</body>
</html>