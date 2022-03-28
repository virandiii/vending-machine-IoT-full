<?php
$koneksi    = mysqli_connect("localhost", "root", "", "ven");
$label1 = ["Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"];
 
for($bulan = 1;$bulan < 13;$bulan++)
{
	$query = mysqli_query($koneksi,"select sum(jumlah) as jumlah from topup where MONTH (date)='$bulan'");
	$row = $query->fetch_array();
	$jumlah_produk[] = $row['jumlah'];  //$data = mysqli_fetch_assoc($query);

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
 
 
	<script>
		var ctx = document.getElementById("myChart").getContext('2d');
		var myChart = new Chart(ctx, {
			type: 'line',
			data: { 
				labels: <?php  echo json_encode($label1); ?>,
				datasets: [{
					label: 'Total Topup',
					fill: false,
                    lineTension: 0.5,
					backgroundColor: "rgba(250, 69, 1, 1)",
					opacity: 0.5,
                    borderColor: "rgba(250, 69, 1, 1)",
                    pointHoverBackgroundColor: "rgba(250, 69, 1, 1)",
						        pointHoverBorderColor: "rgba(250, 69, 1, 1)",
					data: <?php echo json_encode($jumlah_produk); ?>,
					borderWidth: 1
					
				}]
			},
			options: {
				scales: {
					yAxes: [{
						ticks: {
							beginAtZero:true
						}
					}],
          
				}
			}
		});

    
	</script>
</body>
</html>