<?php
$servername = "127.0.0.1:3307";
$username = "root";
$password = "";
$dbname = "dungbodoi";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$conn->set_charset("utf8");
var_dump($_POST);
$stmt = $conn->prepare("INSERT INTO dung1 (ten, sodienthoai) VALUES (?, ?)");
$stmt->bind_param("ss", $ten, $sodienthoai);

$ten = $_POST['ten'];
$sodienthoai = $_POST['sodienthoai'];

$stmt->execute();

if ($stmt->affected_rows >= 0) {
    echo "Dữ liệu đã được lưu vào cơ sở dữ liệu";
} else {
    echo "Lỗi: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
