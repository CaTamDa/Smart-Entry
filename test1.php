<!DOCTYPE html>
<html lang="en">
<head>
  <meta http-equiv="refresh" content="3">
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Entry</title>
  <style>
    body {
      font-family: 'Poppins', sans-serif;
      background: linear-gradient(135deg, #1e3c72, #2a5298);
      margin: 0;
      padding: 0;
      color: #f4f4f9;
    }
    .container {
      max-width: 800px;
      margin: 50px auto;
      padding: 20px;
      background: linear-gradient(145deg, #1c1f24, #2b2f36);
      border-radius: 15px;
      box-shadow: 5px 5px 15px rgba(0, 0, 0, 0.3);
    }
    h1 {
      text-align: center;
      margin-bottom: 20px;
      color: #ffffff;
      font-size: 2.5rem;
      text-transform: uppercase;
      letter-spacing: 2px;
      background: linear-gradient(90deg, #00d2ff, #3a7bd5);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }
    table {
      width: 100%;
      border-collapse: collapse;
      margin-top: 20px;
      background: linear-gradient(120deg, #1f1f1f, #343a40);
      border-radius: 10px;
      overflow: hidden;
    }
    th, td {
      padding: 15px;
      text-align: left;
      font-size: 1rem;
      border: none;
      color: #ffffff;
    }
    th {
      background-color: #007bff;
      color: white;
      font-size: 1.1rem;
      text-transform: uppercase;
    }
    tr:nth-child(even) {
      background-color: #23272b;
    }
    tr:nth-child(odd) {
      background-color: #1d2124;
    }
    tr:hover {
      background-color: #495057;
      transition: background-color 0.3s ease;
    }
    .footer {
      text-align: center;
      margin-top: 30px;
      font-size: 0.9rem;
      color: #adb5bd;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Smart entry</h1>
    <table>
      <thead>
        <tr>
          <th>Tên</th>
          <th>Thông Tin Liên Lạc</th>
          <th>Ngày Giờ</th>
        </tr>
      </thead>
      <tbody id="contactTable">
        <!-- Data will be inserted here dynamically -->
      </tbody>
    </table>
  </div>
  <div class="footer">&copy; 2025 Contact Manager</div>

  <script>
    // Fetch data from the PHP backend
    fetch('http://localhost:8080/Smartentry/contacts.php') // Thay bằng URL của bạn
      .then(response => response.json())
      .then(data => {
        const tableBody = document.getElementById('contactTable');
        data.forEach(item => {
          const row = document.createElement('tr');
          row.innerHTML = `
            <td>${item.name}</td>
            <td>${item.contact}</td>
            <td>${item.datetime}</td>
          `;
          tableBody.appendChild(row);
        });
      })
      .catch(error => console.error('Error fetching data:', error));
  </script>
</body>
</html>
