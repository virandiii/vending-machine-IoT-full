<?php 



$servername = "localhost";
$username = "root";
$password = "";
$database = "ven";

$conn = mysqli_connect($servername, $username, $password, $database);

function query($query){
	global $conn;
	$hasil = mysqli_query($conn, $query);
	$rows = [];
	while( $row = mysqli_fetch_assoc($hasil)){
		$rows[] = $row;
	}
	return $rows;
}


function hapus($no){
	global $conn;
	mysqli_query($conn, "DELETE FROM rfid WHERE no = $no");

return mysqli_affected_rows($conn);
}

function tambah($data){
	global $conn;
	$idcard = htmlspecialchars($data["idcard"]);
	$nama  = htmlspecialchars($data["nama"]);
	$now = new DateTime();
	$datenow = $now->format("Y-m-d H:i:s");
		$query = "INSERT INTO rfid VALUES('','$idcard','$nama','$datenow','')";

	mysqli_query($conn, $query); 

return mysqli_affected_rows($conn);
}

function ubah($data){
	global $conn;

	$no = $data["no"];
	$idcard = htmlspecialchars($data["idcard"]);
	$nama  = htmlspecialchars($data["nama"]);


		$query = "UPDATE rfid SET  idcard = '$idcard', nama = '$nama' WHERE no = $no ";

	mysqli_query($conn, $query); 

return mysqli_affected_rows($conn);
}

function registrasi($data){
	global $conn;

	$username = strtolower(stripslashes( $data["username"]));
	$email = strtolower(stripslashes( $data["email"]));
	$alamat = strtolower(stripslashes( $data["alamat"]));
	$kabupaten = strtolower(stripslashes( $data["kabupaten"]));
	$kecamatan = strtolower(stripslashes( $data["kecamatan"]));
	$kodepos = strtolower(stripslashes( $data["kodepos"]));
	$password = mysqli_real_escape_string($conn, $data["password"]);
	$password2 = mysqli_real_escape_string($conn, $data["password2"]);

 	$result = mysqli_query ($conn, "SELECT username FROM user WHERE username = '$username' ");
 	
 	if (mysqli_fetch_assoc ($result) ){
 		echo "
 		<script>
 			alert('Username sudah Terdaftar');
 		</script>
 		";
 		return false;
 	}

	if ( $password !== $password2){
		echo "
		<script>
		alert('Konfirmasi Password Tidak Sesuai')
		</script>
		";

		return false;
	} 

	$password = password_hash($password, PASSWORD_DEFAULT);
	mysqli_query($conn, "INSERT INTO user VALUES('', '$username', '$email', '$alamat', '$kabupaten', '$kecamatan', '$kodepos', '$password')");

	return mysqli_affected_rows($conn);
}

function readrfid($query){
	global $conn;
	$hasil = mysqli_query($conn, $query);
	$rows = [];
	while( $row = mysqli_fetch_assoc($hasil)){
		$rows[] = $row;
	}
	return $rows;
}

?>
