#include <WiFiS3.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <UTF8String.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16 columns, 2 rows
String ten, sodienthoai;
// Init array that will store new NUID 
byte nuidPICC[4];
String tmp="";
// Thay thế bằng thông tin WiFi của bạn
const char* ssid = "802 2.4GHz";
const char* password = "0971947505";

// Thay thế bằng địa chỉ IP hoặc tên miền và cổng của server
const char* server = "192.168.72.113";
const int port = 8080; // Port mặc định cho HTTP

void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  //Serial.println(F("Xin chào"));
  //Serial.println(F("This code scan the MIFARE Classsic NUID."));
  //Serial.print(F("Using the following key:"));
  //printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

// Initialize LCD
    lcd.init();
    lcd.backlight(); // Turn on LCD backlight
    lcd.clear();

// Display initial message
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting..");
  


  // Kết nối WiFi
  WiFi.begin(ssid, password);
  if (WiFi.status() == WL_CONNECTED) {
    //delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scan your card");
    //Serial.print(".");
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connection failed");
  }

  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}

void loop() {
  //int sensorValue = analogRead(A0);  // Đọc giá trị từ cảm biến nối với chân A0
  //Serial.println(sensorValue);       // Gửi giá trị qua cổng serial
  //delay(1000);                       // Đợi 1 giây trước khi gửi giá trị tiếp theo

    
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent() ||  ! rfid.PICC_ReadCardSerial())
    {return;}
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Card have been");
    lcd.setCursor (0,1);
    lcd.print("scanned");
  }

  // Verify if the NUID has been readed
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    //Serial.println(F("The NUID tag is:"));
    //Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    //Serial.print(tmp);
    //Serial.println();
  }
  else {
    Serial.println(F("Card read previously."));
    //return;
    delay(3000);
  }
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

  if(tmp == "20102454"){
    ten = "Phan Tiến Dũng";
    sodienthoai = "0395926492";
  }
  else if( tmp == "1051312011"){
    ten = "Nguyễn Văn A";
    sodienthoai = "011234568";
  }
  else if( tmp == "22715712119"){
    ten = "Nguyễn văn B";
    sodienthoai = "0811654656";
  }

  Serial.println(ten);
  Serial.println(sodienthoai);


  // Tạo kết nối tới server
  
    //const char* server = "192.168.72.113";
    //192.168.1.57
    //const int port = 8080;
    const char* url = "/Smartentry/receive_data.php";
    WiFiClient client;  
    if (!client.connect(server, port)) {
        Serial.println("Connection failed");
        return;
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Thank you");
      delay(2000);
    }

    //String ten = "Dũng";
    //String sodienthoai = "0395926492";
    String data = "ten=" + ten + "&sodienthoai=" + sodienthoai;
    Serial.println(data);
    client.print("POST " + String(url) + " HTTP/1.1\r\n");
    client.print("Host: ");
    client.println(server);
    client.print("Content-Type: application/x-www-form-urlencoded\r\n");
    client.print("Content-Length: ");
    client.println(data.length());
    client.print("\r\n");
    client.print(data);

    while (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
    }

    client.stop();
    delay(1000);
    return;
}





/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  tmp="";
  for (byte i = 0; i < bufferSize; i++) {
    
    tmp = tmp +  String(buffer[i]);
    //Serial.println();
    //Serial.print(tmp);
    //Serial.print(' ');
    //Serial.print(buffer[i], DEC);
  }
  //Serial.println();
  //Serial.print(tmp);
}
