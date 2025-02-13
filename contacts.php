<?php
// Kết nối đến CSDL
$servername = "127.0.0.1:3307"; // Hoặc "localhost:3307"
$username = "root"; // Thay bằng username của bạn
$password = ""; // Thay bằng password của bạn
$dbname = "dungbodoi";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
//$conn->set_charset("utf8");
// Lấy dữ liệu từ bảng dung1
$sql = "SELECT ten, sodienthoai, thoigian FROM dung1"; // Sửa lại tên bảng nếu cần
$result = $conn->query($sql);

$data = array();

if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        $data[] = array(
            "name" => $row["ten"],
            "contact" => $row["sodienthoai"],
            "datetime" => $row["thoigian"]
        );
    }
}

// Chuyển dữ liệu sang định dạng JSON và trả về cho JavaScript
header('Content-Type: application/json; charset=utf-8');
echo json_encode($data);

$conn->close();
?>
