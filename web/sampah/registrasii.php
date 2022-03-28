<?php 


require 'koneksi.php';

if (isset($_POST["register"])) {
	
	if (registrasi($_POST) > 0) {
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
	<title>Sign Up</title>
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
						Sign Up
					</span>
				</div>

                <form class="login100-form validate-form"  action="" method="post">
					<div class="wrap-input100 validate-input m-b-26" data-validate="Username is required">
                    <label for="username">Username :</label>
                        <input class="input100" type="text" name="username" id="username" placeholder="Enter username" required="">
						<span class="focus-input100"></span>
					</div>

					<div class="wrap-input100 validate-input m-b-26" data-validate="email is required">
                    <label for="email">Email :</label>
                        <input class="input100" type="text" name="email" id="email" placeholder="Enter Email" required="">
						<span class="focus-input100"></span>
					</div>

					<div class="wrap-input100 validate-input m-b-26" data-validate="alamat is required">
                    <label for="alamat">Alamat :</label>
                        <input class="input100" type="text" name="alamat" id="alamat" placeholder="Enter Alamat" required="">
						<span class="focus-input100"></span>
					</div>

					<div class="wrap-input100 validate-input m-b-26" data-validate="kabupaten is required">
                    <label for="kabupaten">Kabupaten :</label>
                        <input class="input100" type="text" name="kabupaten" id="kabupaten" placeholder="Enter Kabupaten" required="">
						<span class="focus-input100"></span>
					</div>

					<div class="wrap-input100 validate-input m-b-26" data-validate="kecamatan is required">
                    <label for="kecamatan">Kecamatan :</label>
                        <input class="input100" type="text" name="kecamatan" id="kecamatan" placeholder="Enter Kecamatan" required="">
						<span class="focus-input100"></span>
					</div>

					<div class="wrap-input100 validate-input m-b-26" data-validate="kodepos is required">
                    <label for="kodepos">Kode Pos :</label>
                        <input class="input100" type="text" name="kodepos" id="kodepos" placeholder="Enter Kode Pos" required="">
						<span class="focus-input100"></span>
					</div>

					<div class="wrap-input100 validate-input m-b-18" data-validate = "Password is required">
                    <label for="password">Password :</label>
						<input class="input100" type="password" name="password" id="password" placeholder="Enter password" required="">
						<span class="focus-input100"></span>
                    </div>
                    
                    <div class="wrap-input100 validate-input m-b-18" data-validate = "Password is required">
                    <label for="password2">Konfirmasi Password :</label>
						<input class="input100" type="password" name="password2" id="password2" placeholder="Enter password" required="">
						<span class="focus-input100"></span>
                    </div>
                    <div class="flex-sb-m w-full p-b-30">
                    <div>
							<a href="login.php" class="txt1">
                                <link href="login.php">
                                Login?
							</a>
                        </div>
                        </div>

                    <div class="container-login100-form-btn">
						<button class="login100-form-btn" type="submit" name="register">Register</button>
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