<?php 

session_start();

if (isset($_SESSION["login"])){
	header("Location: examples/dashboard.php");
	exit;
}

require 'examples/koneksi.php';

if (isset($_POST["register"])) {
	
	if (registrasiadmin($_POST) > 0) {
		echo "
		<script>
			alert('User Baru Berhasil di Tambahkan');
		</script>
			 ";
		}	else 
		{
			echo mysqli_error($conn);
		}
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
	<title>Register</title>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
<!--===============================================================================================-->	
	<link rel="icon" type="image/png" href="assets/images/icons/favicon.ico"/>
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/vendor/bootstrap/css/bootstrap.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/fonts/font-awesome-4.7.0/css/font-awesome.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/fonts/Linearicons-Free-v1.0.0/icon-font.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/vendor/animate/animate.css">
<!--===============================================================================================-->	
	<link rel="stylesheet" type="text/css" href="assets/vendor/css-hamburgers/hamburgers.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/vendor/animsition/css/animsition.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/vendor/select2/select2.min.css">
<!--===============================================================================================-->	
	<link rel="stylesheet" type="text/css" href="assets/vendor/daterangepicker/daterangepicker.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="assets/css/util.css">
	<link rel="stylesheet" type="text/css" href="assets/css/main.css">
<!--===============================================================================================-->
</head>
<body>

	
	<div class="limiter">
		<div class="container-login100">
			<div class="wrap-login100">
				<div class="login100-form-title" style="background-image: url(assets/img/log.jpg);">
					<span class="login100-form-title-1">
						Register Admin
					</span>
				</div>

				<form class="login100-form validate-form" action="" method="post">

				
		<li>
        <div class="wrap-input100 validate-input m-b-26" data-validate="Username is required">
			<label for="username">Username :</label>
			<input class="input100" type="text" name="username" id="username" placeholder="Enter username" required="">
            <span class="focus-input100"></span>
					</div>
		

		
            <div class="wrap-input100 validate-input m-b-18" data-validate="Username is required">
			<label for="password">Password :</label>
			<input class="input100" type="password" name="password" id="password" placeholder="Enter Password" required="">
            <span class="focus-input100"></span>
            </div>
		

		
            <div class="wrap-input100 validate-input m-b-26" data-validate="Username is required">
			<label for="password2">Konfirmasi Password</label>
			<input class="input100" type="password" name="password2" placeholder="Enter Password" id="password2" required="">
            <span class="focus-input100"></span>
            </div>	
		

		
			<button type="submit" name="register">Register</button>	
</br>
			<input type="button" value="Login" onclick="window.location.href='login.php'" />
		</li>
	</ul>

    </form>




						
					</div>
				</form>
			</div>
		</div>
	</div>

<!--===============================================================================================-->
	<script src="assets/vendor/jquery/jquery-3.2.1.min.js"></script>
<!--===============================================================================================-->
	<script src="assets/vendor/animsition/js/animsition.min.js"></script>
<!--===============================================================================================-->
	<script src="assets/vendor/bootstrap/js/popper.js"></script>
	<script src="assets/vendor/bootstrap/js/bootstrap.min.js"></script>
<!--===============================================================================================-->
	<script src="assets/vendor/select2/select2.min.js"></script>
<!--===============================================================================================-->
	<script src="assets/vendor/daterangepicker/moment.min.js"></script>
	<script src="assets/vendor/daterangepicker/daterangepicker.js"></script>
<!--===============================================================================================-->
	<script src="assets/vendor/countdowntime/countdowntime.js"></script>
<!--===============================================================================================-->
	<script src="assets/js/main.js"></script>

</body>
</html>