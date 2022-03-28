#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include "CTBot.h";
#include <EEPROM.h>;

LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient client;

#define RST_PIN         0           // Configurable, see typical pin layout above
#define SS_PIN          2          // Configurable, see typical pin layout abovez

String u;

//String request_string;

String token = "1811737358:AAFW2bQPvOoQuIeaTZF98OK5s4IW-eYLRtc";
const int idbot = 539038844;

TBMessage msg;
CTBot mybot;
int dataid = 0; // data
int num1;//stok
int num2;//transaksi

String mac;
String a ;
String arrDataa[3]; //baca jumlah
String tambah[2];
char verifstok[3];
char arrDataaa[3];
char validwaktu[3];
char pilihanstok;


HTTPClient http;
String request_string;
const char* host = "192.168.1.7";
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
int wifi_kom = 0;
int aaa = 0;
int bbb = 0;

const int pinButton = 04;
const int pinButton2 = 02;
const int pinButton3 = 05;
const int pinBuzzer = 16;

const char* ssid = "GALAXY S9";
const char* pass = "bisajadi";

Servo servo;
Servo servo1;
Servo servo2;

int harga_barang;
String id;
char pilihan;
void bacaidpetugas() {

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  MFRC522::StatusCode status;


  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }


  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {


    mac.concat(String(mfrc522.uid.uidByte[i], HEX));
  }



  Serial.println(mac);

  if (mac == "3ab5f5a") {
    mac = "";
    bepp();
    lcd.clear();
    lcd.print("   INPUT STOK   ");
    Serial.println("isi stok manual"); {
      delay(10000);
    }

    String data = "";
    while (Serial.available() > 0)
    {
      data += char(Serial.read());
    }
    data.trim();

    if (data != "")
    {
      int index = 0;
      for (int i = 0; i <= data.length (); i++)
      {
        char delimiter = '>';
        if (data[i] != delimiter)
          tambah[index] += data[i];
        else
          index++;
      }
      Serial.println(tambah[0]);
      Serial.println(tambah[1]);
      Serial.println(tambah[2]);
      String datainput = String(tambah[0]) + ">" + String(tambah[1]) + ">" + String(tambah[2]);
      Serial.println(datainput);
      Serial.println("Verifikasi");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Jumlah");
      lcd.setCursor(8, 0);
      lcd.print(datainput);
      lcd.setCursor(0, 1);
      lcd.print("*/Ya   #/Tidak"); {
        delay(7000);
      }

      String data = "";
      while (Serial.available() > 0)
      {
        data += char(Serial.read());
      }
      delay (3000);
      data.trim();


      if (data != "")
      {
        int index = 0;
        for (int i = 0; i <= data.length (); i++)
        {
          char delimiter = '&';
          if (data[i] != delimiter)
            verifstok[index] += data[i];
          else
            index++;
        }

        char pilihanstok = verifstok[0];
        if (pilihanstok == '*') {

          verifstok[0] = '\0';
          Serial.println(pilihanstok);
          int y = tambah[0].toInt();
          int r = tambah[1].toInt();
          int m = tambah[2].toInt();

          if (y > 0) {
            EEPROM.write(0, y);
            EEPROM.commit();

          } if (r > 0) {
            EEPROM.write(2, r);
            EEPROM.commit();

          } if (m > 0) {
            EEPROM.write(4, m);
            EEPROM.commit();

          }
          lcd.clear();
          lcd.print("-----Sukses-----"); {
            delay(2000);
          }
          Serial.println("update sukses");
        }

        int parameterupdate = 1;
        EEPROM.write(8, parameterupdate);
        EEPROM.commit();

        int abc = EEPROM.read(8);
        Serial.println(abc);
        
        tambah [0] = "";
        tambah [1] = "";
        tambah [2] = "";


      }
      else if (pilihanstok == '#' ) {
        verifstok[0] = '\0';
        tambah [0] = "";
        tambah [1] = "";
        tambah [2] = "";
        Serial.print("Masukan jumlah stok : ");
        lcd.clear();
        lcd.print("   INPUT STOK   "); {
          delay(5000);
        }
        bacaidpetugas();
      }

    }
    lcd.clear();
    lcd.print("----Welcome----");
    tambah [0] = "";
    tambah [1] = "";
    tambah [2] = "";
    return;
  } else {
    bepp();
    lcd.clear();
    lcd.print("-ID KARTU SALAH-");
    delay(3000);
    Serial.print("ID belum terdaftar");
  }
  mac = "";
  lcd.clear();
  lcd.print("----Welcome----");
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

}
void bepp() {
  //nada pendek
  digitalWrite(pinBuzzer, HIGH);
  delay(200);
  digitalWrite(pinBuzzer, LOW);
  delay(200);
}
void bepp1() {
  //nada pendek
  digitalWrite(pinBuzzer, HIGH);
  delay(100);
  digitalWrite(pinBuzzer, LOW);
  delay(100);
  digitalWrite(pinBuzzer, HIGH);
  delay(100);
  digitalWrite(pinBuzzer, LOW);
  delay(100);
}
void updatestokeeprom() {
  int id1 = EEPROM.read(0);
  if (id1 != 0) {
    Serial.print("Jumlah Stok : ");
    Serial.println(id1);
    HTTPClient http;
    request_string = "http://192.168.1.7/ven/epromtambah.php?id=";
    request_string += 1;
    request_string += "&stok=";
    request_string += id1;
    Serial.print("requesting URL: ");
    Serial.println(request_string);
    http.begin(request_string);
    auto httpCode = http.GET();

    String payload = http.getString();
    // Serial.println(request_string);
    Serial.println(payload);
    EEPROM.commit();
    http.end();
  }
  int id2 = EEPROM.read(2);
  if (id2 != 0 ) {
    Serial.print("Jumlah Stok : ");
    Serial.println(id1);
    HTTPClient http;
    request_string = "http://192.168.1.7/ven/epromtambah.php?id=";
    request_string += 2;
    request_string += "&stok=";
    request_string += id2;
    Serial.print("requesting URL: ");
    Serial.println(request_string);
    http.begin(request_string);
    auto httpCode = http.GET();

    String payload = http.getString();
    // Serial.println(request_string);
    Serial.println(payload);
    EEPROM.commit();
    http.end();
  }
  int id3 = EEPROM.read(4);
  if (id3 != 0) {
    Serial.print("Jumlah Stok : ");
    Serial.println(id3);
    HTTPClient http;
    request_string = "http://192.168.1.7/ven/epromtambah.php?id=";
    request_string += 3;
    request_string += "&stok=";
    request_string += id3;
    Serial.print("requesting URL: ");
    Serial.println(request_string);
    http.begin(request_string);
    auto httpCode = http.GET();

    String payload = http.getString();
    // Serial.println(request_string);
    Serial.println(payload);
    EEPROM.commit();
    http.end();
  }
  EEPROM.write(8, 0);
  EEPROM.commit();
}
void kirimtransaksisementara() {

  int item1 = EEPROM.read(1); //read address on eeprom

  item1 = (item1 * 1);
  Serial.print("jumlah transaksi : ");
  Serial.println(item1);
  lcd.clear();
  lcd.print("Update  Database");
  if (item1 > 0) {
    for (int i = 0; i < item1; i++) {
      Serial.println("Kirim ke database : ");
      HTTPClient http;
      String idmakanan = "1" ;
      http.begin("http://192.168.1.7/ven/penjualanbaru.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST("id=" + idmakanan);
      if (httpResponseCode > 0) {
        Serial.println (httpResponseCode);
      }
      kur();
      terjual();
      transaksi();
      http.end();
      delay(2000);
    }

    EEPROM.write(1, 0);
    EEPROM.commit();
  }

  int item2 = EEPROM.read(3); //read address on eeprom

  item2 = (item2 * 1);
  Serial.print("jumlah transaksi : ");
  Serial.println(item2);
  if (item2 > 0) {
    for (int i = 0; i < item2; i++) {
      Serial.println("Kirim ke database : ");
      HTTPClient http;
      String idmakanan2 = "2" ;
      http.begin("http://192.168.1.7/ven/penjualanbaru.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST("id=" + idmakanan2);
      if (httpResponseCode > 0) {
        Serial.println (httpResponseCode);
      }
      kur();
      terjual();
      transaksi();
      http.end();
      delay(2000);
    }
    EEPROM.write(3, 0);
    EEPROM.commit();
  }


  int item3 = EEPROM.read(5); //read address on eeprom

  item3 = (item3 * 1);
  Serial.print("jumlah transaksi : ");
  Serial.println(item3);
  if (item3 > 0) {
    for (int i = 0; i < item3; i++) {
      Serial.println("Kirim ke database : ");
      HTTPClient http;
      String idmakanan3 = "3" ;
      http.begin("http://192.168.1.7/ven/penjualanbaru.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST("id=" + idmakanan3);
      if (httpResponseCode > 0) {
        Serial.println (httpResponseCode);
      }
      kur();
      terjual();
      transaksi();
      http.end();
      delay(2000);
    }
    EEPROM.write(5, 0);
    EEPROM.commit();
  }
  lcd.clear();
  lcd.print("----Welcome----");
}

//*****************************************************************************************//
void konekWifi()
{
  lcd.begin();
  lcd.backlight();
  lcd.print("----Welcome----");
  WiFi.disconnect();
  Serial.println("Wifi Terputus !!!");
  lcd.clear();
  lcd.print("_Disconnect_");{
    delay(1000);
  }
  lcd.clear();
  lcd.print("----Welcome----");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");{
      delay(1000);
    }
    bacaidpetugas();
    bacastokeprom();
    if (bbb != 3)
    {
      bbb = bbb + 1;
    }
    milih();
  }


  Serial.println("Connected..");
  kirimtransaksisementara();
  int bacadata = EEPROM.read(8);
  Serial.println(bacadata);
  if (bacadata == 0) {
    sinkrondatabase();
  }
  if (bacadata == 1) {
    updatestokeeprom();
  }
  lcd.clear();
  lcd.print("Wifi Connected");
  //koneksi wifi
  mybot.wifiConnect(ssid, pass);
  //set token
  mybot.setTelegramToken(token);

  //cek koneksi
  if (mybot.testConnection())
    Serial.println("Konek Telegram");
  else
    Serial.println("Konek");

  lcd.clear();
  lcd.print("----Welcome----");



  Serial.println("Connected to the WiFi network");
}

void reconNetwork() {
  konekWifi();
}

void rebaca() {
  jumlah();
}

void cekKoneksi()
{
  //cek koneksi wifi
  if (WiFi.status() != WL_CONNECTED || WiFi.status() == WL_DISCONNECTED)
  {
    Serial.println("Wifi Terputus");
    lcd.clear();
    lcd.print("_Disconnect_");{
      delay(1000);
    }
    wifi_kom = 0;
    bbb = 0;
    //client.disconnect();
    delay(1000);
    reconNetwork();
  }
  else if (WiFi.status() != WL_DISCONNECTED)
  {
    if (wifi_kom != 2)
    {
      wifi_kom = 1;
      if (wifi_kom == 1)
      {
        Serial.println("Wifi ok");
        wifi_kom = 2;
      }
    }
  }
}

void simpen1() {
  id = "1";
  int dataid = id.toInt() ;

  int item1 = EEPROM.read(1);

  item1 = (item1 * 1);

  delay(1000);
  int u = arrDataa[0].toInt();
  num2 = (item1 + u);
  Serial.print("simpan jumlah transaksi  item 1: ");
  Serial.println(num2);
  EEPROM.write(1, num2);
  EEPROM.commit();

}

void simpen2() {
  id = "2";
  int dataid = id.toInt() ;

  int item2 = EEPROM.read(3);

  item2 = (item2 * 1);

  delay(1000);
  int u = arrDataa[0].toInt();
  num2 = (item2 + u);
  Serial.print("siimpan jumlah transaksi item 2: ");
  Serial.println(num2);
  EEPROM.write(3, num2);
  EEPROM.commit();

}

void simpen3() {
  id = "3";
  int dataid = id.toInt() ;

  int item3 = EEPROM.read(5);

  item3 = (item3 * 1);

  delay(1000);
  int u = arrDataa[0].toInt();
  num2 = (item3 + u);
  Serial.print("simpan jumlah transaksi item 3: ");
  Serial.println(num2);
  EEPROM.write(5, num2);
  EEPROM.commit();

}
void bacastokeprom(){
  
  int makanan1 = EEPROM.read(0);
  int makanan2 = EEPROM.read(2);
  int makanan3 = EEPROM.read(4);
  Serial.print("Stok Item 1 Pada EEPROM :");
  Serial.println(makanan1);
  Serial.print("Stok Item 2 Pada EEPROM :");
  Serial.println(makanan2);
  Serial.print("Stok Item 3 Pada EEPROM :");
  Serial.println(makanan3);
  
  
}
void cek() {
  //cek
  if (WiFi.status() != WL_CONNECTED || WiFi.status() == WL_DISCONNECTED)
  {
    lcd.clear();
    lcd.print("PembelianOffline");
    wifi_kom = 0;
    bbb = 0;
    //client.disconnect();
    delay(1000);
    simpen1();
  }

}

void cek2() {
  //cek
  if (WiFi.status() != WL_CONNECTED || WiFi.status() == WL_DISCONNECTED)
  {
    lcd.clear();
    lcd.print("PembelianOffline");
    wifi_kom = 0;
    bbb = 0;
    //client.disconnect();
    delay(1000);
    simpen2();
  }

}

void cek3() {
  //cek
  if (WiFi.status() != WL_CONNECTED || WiFi.status() == WL_DISCONNECTED)
  {
    lcd.clear();
    lcd.print("PembelianOffline");
    wifi_kom = 0;
    bbb = 0;
    //client.disconnect();
    delay(1000);
    simpen3();
  }

}

void sinkrondatabase() {
  Serial.println("Sinkron data stok");

  id = "1";
  if (id = 1) {
    Serial.println(id);

    HTTPClient http;
    request_string = "http://192.168.1.7/ven/ambil.php?id=";
    request_string += id;

    Serial.print("requesting URL: ");
    Serial.print(request_string);
    http.begin(request_string);
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      //Serial.println("Stok Habis");
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
      int stok1 = payload.toInt();
      Serial.println(stok1); //Print the response payload


      if (stok1 >= 0) {
        EEPROM.write(0, stok1);
        EEPROM.commit();
        http.end();
      }
    }
  }

  id = "2";
  if (id = 2) {
    Serial.println(id);

    HTTPClient http;
    request_string = "http://192.168.1.7/ven/ambil.php?id=";
    request_string += id;

    Serial.print("requesting URL: ");
    Serial.print(request_string);
    http.begin(request_string);
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      //Serial.println("Stok Habis");
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
      int stok2 = payload.toInt();
      Serial.println(stok2); //Print the response payload


      if (stok2 >= 0) {
        EEPROM.write(2, stok2);
        EEPROM.commit();
        http.end();
      }
    }
  }


  id = "3";
  if (id = 3) {
    Serial.println(id);

    HTTPClient http;
    request_string = "http://192.168.1.7/ven/ambil.php?id=";
    request_string += id;

    Serial.print("requesting URL: ");
    Serial.print(request_string);
    http.begin(request_string);
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      //Serial.println("Stok Habis");
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
      int stok3 = payload.toInt();
      Serial.println(stok3); //Print the response payload


      if (stok3 >= 0) {
        EEPROM.write(4, stok3);
        EEPROM.commit();
        http.end();
      }
    }
  }
}
void setup() {
  //----setup
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(6000);
  digitalWrite(2, HIGH);
  pinMode(pinBuzzer, OUTPUT);
  delay(1000);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  EEPROM.begin (512);
  lcd.begin();
  lcd.print("Disconnect.."); {
    delay(1000);
  }
  konekWifi();
}

String strID, val, data;
unsigned long timenow = 0;


void serv1() {
  Serial.print("Putar");
  servo.attach(03);
  servo.writeMicroseconds(2000);
  delay(3000);
  servo.writeMicroseconds(1500);
  delay(100);
  return;

}

void serv2() {
  servo1.attach(01);
  servo1.writeMicroseconds(2000);
  delay(3000);
  servo1.writeMicroseconds(1500);
  delay(100);
  return;
}

void serv3() {
  servo2.attach(15);
  servo2.writeMicroseconds(2000);
  delay(3000);
  servo2.writeMicroseconds(1500);
  delay(100);
  return;
}


void jumlah() {

  String data = "";
  while (Serial.available() > 0)
  {
    data += char(Serial.read());
  }
  delay (3000);
  data.trim();


  if (data != "")
  {
    int index = 0;
    for (int i = 0; i <= data.length (); i++)
    {
      char delimiter = '#';
      if (data[i] != delimiter)
        arrDataa[index] += data[i];
      else
        index++;
    }
    u = arrDataa[0];
    long u = arrDataa[0].toInt();
    if (u > 0) {
      lcd.setCursor(1, 1);
      lcd.print(u);
      Serial.println(u);
    }
    else if (u < 0 ) {
      Serial.println("Gagal");
    }
  }
  //delay(3000);

}

void beli_item(int harga) {


  lcd.begin();
  lcd.backlight();


  if ( harga_barang == 3000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("----Tap Kartu---");
    lcd.setCursor(0, 1);
    lcd.print("Twister");
    lcd.setCursor(7, 1);
    lcd.print("Rp.");
    lcd.setCursor(10, 1);
    u = arrDataa[0];
    long u = arrDataa[0].toInt();
    int layar = harga_barang * u;
    lcd.print(layar); {
      delay(2000);
    }
    lcd.clear();

    lcd.print("--Please  Wait--"); {
      delay(2000);
    }
    lcd.clear();

  }

  if ( harga_barang == 2000) {
    lcd.setCursor(0, 0);
    lcd.print("----Tap Kartu---");
    lcd.setCursor(0, 1);
    lcd.print("Lays");
    lcd.setCursor(7, 1);
    lcd.print("Rp.");
    lcd.setCursor(10, 1);
    u = arrDataa[0];
    long u = arrDataa[0].toInt();
    int layar = harga_barang * u;
    lcd.print(layar); {
      delay(2000);
    }
    lcd.clear();
    lcd.print("--Please  Wait--"); {
      delay(2000);
    }
    lcd.clear();

  }

  if ( harga_barang == 1000) {
    lcd.setCursor(0, 0);
    lcd.print("----Tap Kartu---");
    lcd.setCursor(0, 1);
    lcd.print("Soba");
    lcd.setCursor(6, 1);
    lcd.print("Rp.");
    lcd.setCursor(9, 1);
    u = arrDataa[0];
    long u = arrDataa[0].toInt();
    int layar = harga_barang * u;
    lcd.print(layar); {
      delay(2000);
    }
    lcd.clear();
    lcd.print("--Please  Wait--"); {
      delay(2000);
    }
    lcd.clear();
  }
  pembayaran(harga_barang);



}

void pembayaran(int harga) {
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("**Card Detected:**");

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print("Saldo: ");

  byte buffer1[18];
  char tampung[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");



  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }


  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
    tampung[i] = buffer2[i];
  }

  //baca
  String stampung = String(tampung);
  Serial.println();
  Serial.println("--------------------------");
  Serial.print("CHAR : ");
  Serial.println(stampung);
  int firstIndex = stampung.indexOf('<');
  int lastIndex = stampung.indexOf('>');
  String hasil = stampung.substring(firstIndex + 1, lastIndex);
  Serial.println("--------------------------");
  Serial.print("BALANCE : ");
  Serial.println(hasil);
  Serial.println("--------------------------");
  int a = hasil.toInt();
  int b = harga;
  int c = a - b;
  Serial.println(c);



  //tulis
  if (a >= b) {
    String input1 = String(c);
    String input2 = "<" + input1 + ">";
    byte plain[input2.length()];

    input2.getBytes(plain, input2.length());

    // Write block
    status = mfrc522.MIFARE_Write(block, plain, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Write() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    if (b == 3000) {
      Serial.println("Please Take");
      int value = EEPROM.read(0); //read address on eeprom

      value = (value * 1);
      delay(1000);
      int u = arrDataa[0].toInt();
      num1 = value - u;
      Serial.print("sisa stok : ");
      Serial.println(num1); // show result read on eeprom
      EEPROM.write(0, num1);
      EEPROM.commit();

      cek();
      if (u > 0) {
        for (int i = 0; i < u; i++) {
          kur();
          terjual();
          transaksi();
          serv1();
          arrDataa[0] = "";
        }
      }
    }

    if (b == 2000) {
      Serial.println("Please Take");
      int value = EEPROM.read(2); //read address on eeprom

      value = (value * 1);
      delay(1000);
      int u = arrDataa[0].toInt();
      num1 = value - u;
      Serial.print("sisa stok : ");
      Serial.println(num1); // show result read on eeprom
      EEPROM.write(2, num1);
      EEPROM.commit();

      cek2();
      if (u > 0) {
        for (int i = 0; i < u; i++) {
          kur();
          terjual();
          transaksi();
          serv2();
          arrDataa[0] = "";
        }
      }

    }

    if (b == 1000) {
      Serial.println("Please Take");
      int value = EEPROM.read(4); //read address on eeprom

      value = (value * 1);
      delay(1000);
      int u = arrDataa[0].toInt();
      num1 = value - u;
      Serial.print("sisa stok : ");
      Serial.println(num1); // show result read on eeprom
      EEPROM.write(4, num1);
      EEPROM.commit();

      cek3();
      if (u > 0) {
        for (int i = 0; i < u; i++) {
          kur();
          terjual();
          transaksi();
          serv3();
          arrDataa[0] = "";
        }
      }
    }

    else Serial.println(F("MIFARE_Write() success: "));



    lcd.clear();
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("SISA SALDO ANDA :");
    lcd.setCursor(0, 1);
    lcd.print("Rp.");
    lcd.setCursor(2, 1);
    lcd.print(c); {
      delay(2000);
    }
    //serv();
    lcd.clear();
    lcd.print("----Welcome----");
  }


  else if (a < b)
  {
    lcd.begin();
    lcd.backlight();
    lcd.print("Saldo Kurang!!!"); {
      delay(2000);
    }
    lcd.clear();
    lcd.print("----Welcome----");

    Serial.println("Less Balance ");
  }
  //------------------------------------------------------

  Serial.println("\n**End Reading**\n");
  //arrDataa [0] = "";
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(2000);
  //setup();

}

//*****************************************************************************************//
void loop() {

  int value5 = EEPROM.read(0);

  value5 = (value5 * 1);
  Serial.print("baca stok item 1 : ");
  Serial.println(value5);

  int value6 = EEPROM.read(2);
  value6 = (value6 * 1);
  Serial.print("baca stok item 2 : ");
  Serial.println(value6);

  int value7 = EEPROM.read(4);

  value7 = (value7 * 1);
  Serial.print("baca stok item 3 : ");
  Serial.println(value7);
  Serial.println(" ");
  milih2(); {
    delay(1000);
  }

  //chatbottt
  if (mybot.getNewMessage(msg))
  {
    Serial.println("Message :" + msg.text);

    String pesan = msg.text;
    if (pesan == "Check stock")
    {
      HTTPClient http;

      request_string = "http://192.168.1.7/ven/tele.php?";


      Serial.print("requesting URL: ");
      Serial.print(request_string);

      http.begin(request_string);
      int httpCode = http.GET();

      if (httpCode > 0) { //Check the returning code
        //Serial.println("Stok Habis");
        String payload = http.getString();   //Get the request response payload
        mybot.sendMessage(idbot, payload);

      }


      http.end();   //Close connection

    }

  }
  cekKoneksi();
}
void milih () {

  //*****PEMBELIAN OFFLINE*****//
  //item1
  if (digitalRead(pinButton) == LOW) {

    Serial.println("Item 1");
    id = "1";
    Serial.println(id);
    //  kur();

    int value = EEPROM.read(0); //read address on eeprom

    value = (value * 1);
    Serial.print("baca stok : ");
    Serial.println(value); // show result read on eeprom
    delay(3000);

    Serial.println(value); //Print the response payload
    if (value <= 0) {
      Serial.println("Sold out");
      lcd.begin();
      lcd.backlight();
      lcd.print("Sold out"); {
        delay(2000);
      }




    }

    else if (value >= 0) {
      lcd.clear();
      lcd.print(" Masukan Jumlah ");
      Serial.print("Masukan jumlah : "); {
        delay(7000);
      }
      jumlah();
      validasi1();


      lcd.clear();
      lcd.print("----Welcome----");
      arrDataa[0] = "";
      return;

    }
  }
  //item2
  if (digitalRead(pinButton2) == LOW) {

    Serial.println("Item 2");
    id = "2";
    Serial.println(id);
    //  kur();

    int value = EEPROM.read(2); //read address on eeprom

    value = (value * 1);
    Serial.print("baca stok : ");
    Serial.println(value); // show result read on eeprom
    delay(3000);

    Serial.println(value); //Print the response payload
    if (value <= 0) {
      Serial.println("Sold out");
      lcd.begin();
      lcd.backlight();
      lcd.print("Sold out"); {
        delay(2000);
      }
      lcd.clear();
      lcd.print("----Welcome----");
      return;



    }

    else if (value >= 0) {

      lcd.clear();
      lcd.print(" Masukan Jumlah ");
      Serial.print("Masukan jumlah : "); {
        delay(7000);
      }
      jumlah();
      validasi1();
      lcd.clear();
      lcd.print("----Welcome----");
      arrDataa[0] = "";
      return;


    }
  }
  //item3
  if (digitalRead(pinButton3) == LOW) {

    Serial.println("Item 3");
    id = "3";
    Serial.println(id);
    //  kur();

    int value = EEPROM.read(4); //read address on eeprom

    value = (value * 1);
    Serial.print("baca stok : ");
    Serial.println(value); // show result read on eeprom
    delay(3000);

    Serial.println(value); //Print the response payload
    if (value <= 0) {
      Serial.println("Sold out");
      lcd.begin();
      lcd.backlight();
      lcd.print("Sold out"); {
        delay(2000);
      }
      lcd.clear();
      lcd.print("----Welcome----");
      return;



    }

    else if (value >= 0) {
      lcd.clear();
      lcd.print(" Masukan Jumlah ");
      Serial.print("Masukan jumlah : "); {
        delay(7000);
      }
      jumlah();
      validasi1();
      lcd.clear();
      lcd.print("----Welcome----");
      arrDataa[0] = "";
      return;

    }
  }
}

void validasi1() {
  u = arrDataa[0];
  long u = arrDataa[0].toInt();
  if (u <= 0) {
    Serial.print("Data Kosong");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingin Menambah");
    lcd.setCursor(0, 1);
    lcd.print("Waktu? */Ya #/No");
    {
      delay(8000);
    }

    String dataa = "";
    while (Serial.available() > 0)
    {
      dataa += char(Serial.read());
    }
    delay (3000);
    dataa.trim();
    Serial.println(dataa);

    if (dataa != "")
    {
      Serial.println(dataa);
      int index = 0;
      for (int i = 0; i <= dataa.length (); i++)
      {
        char delimiter = '&';
        if (dataa[i] != delimiter)
          validwaktu[index] += dataa[i];
        else
          index++;
      }

      pilihan = validwaktu[0];
      Serial.println(pilihan);
      if (pilihan == '*') {
        validwaktu[0] = '\0';
        Serial.println(pilihan);
        lcd.clear();
        lcd.print("Masukin Jumlah"); {
          delay(6000);
        }
        jumlah();
        validasi2();

      }
    }
    lcd.clear();
    lcd.print("----Welcome----");
    return;
  }

  Serial.println("Verifikasi");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jumlah");
  lcd.setCursor(8, 0);
  lcd.print(u);
  lcd.setCursor(0, 1);
  lcd.print("*/Ya   #/Tidak"); {
    delay(7000);
  }
  String dataa = "";
  while (Serial.available() > 0)
  {
    dataa += char(Serial.read());
  }
  delay (3000);
  dataa.trim();


  if (dataa != "")
  {
    int index = 0;
    for (int i = 0; i <= dataa.length (); i++)
    {
      char delimiter = '&';
      if (dataa[i] != delimiter)
        arrDataaa[index] += dataa[i];
      else
        index++;
    }
    Serial.println(dataa);
    Serial.println(arrDataaa[0]);
    pilihan = arrDataaa[0];
    if (pilihan == '*') {
      Serial.println(pilihan);
      arrDataaa[0] = '\0';
      Serial.println(id);
      int ok = id.toInt();
      if (ok == 1) {
        harga_barang = 3000;
        beli_item(harga_barang);
      }
      if (ok == 2) {
        harga_barang = 2000;
        beli_item(harga_barang);
      }
      if (ok == 3) {
        harga_barang = 1000;
        beli_item(harga_barang);
      }
    }
    else if (pilihan == '#' ) {
      Serial.println(pilihan);
      arrDataaa[0] = '\0';
      arrDataa[0] = "";
      Serial.print("Masukan Jumlah Lagi : ");
      lcd.clear();
      lcd.print(" Masukan Jumlah "); {
        delay(5000);
      }
      jumlah();
      validasi2();

    }
  }
}
void validasi2() {
  u = arrDataa[0];
  long u = arrDataa[0].toInt();
  if (u <= 0) {
    Serial.print("Data Kosong");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingin Menambah");
    lcd.setCursor(0, 1);
    lcd.print("Waktu? */Ya #/No");
    {
      delay(4000);
    }
    String dataa = "";
    while (Serial.available() > 0)
    {
      dataa += char(Serial.read());
    }
    delay (3000);
    dataa.trim();


    if (dataa != "")
    {
      int index = 0;
      for (int i = 0; i <= dataa.length (); i++)
      {
        char delimiter = '&';
        if (dataa[i] != delimiter)
          validwaktu[index] += dataa[i];
        else
          index++;
      }
      Serial.println(pilihan);
      pilihan = validwaktu[0];
      if (pilihan == '*') {
        validwaktu[0] = '\0';
        Serial.println(pilihan);
        jumlah();
        validasi1();

      }
    }
    lcd.clear();
    lcd.print("----Welcome----");
    return;
  }

  Serial.println("Verifikasi");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jumlah");
  lcd.setCursor(8, 0);
  lcd.print(u);
  lcd.setCursor(0, 1);
  lcd.print("*/Ya   #/Tidak"); {
    delay(7000);
  }

  String dataa = "";
  while (Serial.available() > 0)
  {
    dataa += char(Serial.read());
  }
  delay (3000);
  dataa.trim();


  if (dataa != "")
  {
    int index = 0;
    for (int i = 0; i <= dataa.length (); i++)
    {
      char delimiter = '&';
      if (dataa[i] != delimiter)
        arrDataaa[index] += dataa[i];
      else
        index++;
    }
    Serial.println(pilihan);
    pilihan = arrDataaa[0];
    if (pilihan == '*') {
      Serial.println(pilihan);
      int ok = id.toInt();
      if (ok == 1) {
        harga_barang = 3000;
        beli_item(harga_barang);
      }
      if (ok == 2) {
        harga_barang = 2000;
        beli_item(harga_barang);
      }
      if (ok == 3) {
        harga_barang = 1000;
        beli_item(harga_barang);
      }

    }
    else if (pilihan == '#' ) {
      arrDataa[0] = "";
      Serial.print("Masukan Jumlah Lagi : ");
      lcd.clear();
      lcd.print(" Masukan Jumlah "); {
        delay(5000);
      }
      jumlah();
      validasi1();
    }
  }
}


//**********PEMBELIAN ONLINE******************//
void milih2 () {


  //item1
  if (digitalRead(pinButton) == LOW) {

    Serial.println("Item 3");
    id = "1";
    Serial.println(id);


    HTTPClient http;
    request_string = "http://192.168.1.7/ven/ambil.php?id=";
    request_string += id;

    Serial.print("requesting URL: ");
    Serial.print(request_string);
    http.begin(request_string);
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      //Serial.println("Stok Habis");
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
      int q = payload.toInt();
      Serial.println(q); //Print the response payload


      if (q <= 0) {
        mybot.sendMessage(idbot, "Twister Sold out");
        Serial.println("Sold out");
        lcd.begin();
        lcd.backlight();
        lcd.print("Sold Out"); {
          delay(2000);
        }
        lcd.clear();
        lcd.print("----Welcome----");
        return;
        http.end();   //Close connection
      }
      int value = EEPROM.read(0); //read address on eeprom

      value = (value * 1);
      Serial.print("baca stok : ");
      Serial.println(value); // show result read on eeprom
      delay(3000);

      Serial.println(value); //Print the response payload
      if (value <= 0) {
        Serial.println("Sold out");
        lcd.begin();
        lcd.backlight();
        lcd.print("Sold out"); {
          delay(2000);
        }
        lcd.clear();
        lcd.print("----Welcome----");
        return;
      } else if (value >= 0) {

        lcd.clear();
        lcd.print(" Masukan Jumlah ");
        Serial.print("Masukan jumlah : "); {
          delay(7000);
        }
        jumlah();
        u = arrDataa[0];
        long u = arrDataa[0].toInt();
        if (u <= 0) {
          Serial.print("Data Kosong");
          lcd.clear();
          lcd.print("Data Kosong"); {
            delay(4000);
          }
          lcd.clear();
          lcd.print("----Welcome----");
          return;
        }

        Serial.println("Verifikasi");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Jumlah");
        lcd.setCursor(8, 0);
        lcd.print(u);
        lcd.setCursor(0, 1);
        lcd.print("*/Ya   #/Tidak"); {
          delay(7000);
        }

        String data = "";
        while (Serial.available() > 0)
        {
          data += char(Serial.read());
        }
        delay (3000);
        data.trim();

        Serial.println(data);
        if (data != "")
        {
          int index = 0;
          for (int i = 0; i <= data.length (); i++)
          {
            char delimiter = '&';
            if (data[i] != delimiter)
              arrDataaa[index] += data[i];
            else
              index++;
          }

          pilihan = arrDataaa[0];
          if (pilihan == '*') {
            Serial.println(pilihan);
            arrDataaa[0] = '\0';
            harga_barang = 3000;
            beli_item(harga_barang);

          }
          else if (pilihan == '#' ) {
            arrDataa[0] = "";
            arrDataaa[0] = '\0';
            Serial.print("Masukan Jumlah Lagi : ");
            lcd.clear();
            lcd.print(" Masukan Jumlah "); {
              delay(5000);
            }
            jumlah();
            validasi1();
          }
        }
        lcd.clear();
        lcd.print("----Welcome----");
        arrDataa[0] = "";
        return;
      }
    }
  }
  //item2
  if (digitalRead(pinButton2) == LOW) {

    Serial.println("Item 2");
    id = "2";
    Serial.println(id);
    //  kur();

    HTTPClient http;
    request_string = "http://192.168.1.7/ven/ambil.php?id=";
    request_string += id;

    Serial.print("requesting URL: ");
    Serial.print(request_string);
    // client.print(String("GET ") + request_string + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    http.begin(request_string);
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      //Serial.println("Stok Habis");
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
      int q = payload.toInt();
      Serial.println(q); //Print the response payload


      if (q <= 0) {
        mybot.sendMessage(idbot, "Lays Sold out");
        Serial.println("Sold out");
        lcd.begin();
        lcd.backlight();
        lcd.print("Sold Out"); {
          delay(2000);
        }
        lcd.clear();
        lcd.print("----Welcome----");
        return;
        http.end();   //Close connection
      }
      int value = EEPROM.read(2); //read address on eeprom

      value = (value * 1);
      Serial.print("baca stok : ");
      Serial.println(value); // show result read on eeprom
      delay(3000);

      Serial.println(value); //Print the response payload
      if (value <= 0) {
        Serial.println("Sold out");
        lcd.begin();
        lcd.backlight();
        lcd.print("Sold out"); {
          delay(2000);
        }
        lcd.clear();
        lcd.print("----Welcome----");
        return;



      }

      else if (value >= 0) {



        lcd.clear();
        lcd.print(" Masukan Jumlah ");
        Serial.print("Masukan jumlah : "); {
          delay(7000);
        }
        jumlah();
        u = arrDataa[0];
        long u = arrDataa[0].toInt();
        if (u <= 0) {
          Serial.print("Data Kosong");
          lcd.clear();
          lcd.print("Data Kosong"); {
            delay(4000);
          }
          lcd.clear();
          lcd.print("----Welcome----");
          return;
        }

        Serial.println("Verifikasi");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Jumlah");
        lcd.setCursor(8, 0);
        lcd.print(u);
        lcd.setCursor(0, 1);
        lcd.print("*/Ya   #/Tidak"); {
          delay(7000);
        }

        String data = "";
        while (Serial.available() > 0)
        {
          data += char(Serial.read());
        }
        delay (3000);
        data.trim();


        if (data != "")
        {
          int index = 0;
          for (int i = 0; i <= data.length (); i++)
          {
            char delimiter = '&';
            if (data[i] != delimiter)
              arrDataaa[index] += data[i];
            else
              index++;
          }

          pilihan = arrDataaa[0];
          if (pilihan == '*') {
            Serial.println(pilihan);
            arrDataaa[0] = '\0';
            harga_barang = 2000;
            beli_item(harga_barang);

          }
          else if (pilihan == '#' ) {
            arrDataa[0] = "";
            arrDataaa[0] = '\0';
            Serial.print("Masukan Jumlah Lagi : ");
            lcd.clear();
            lcd.print(" Masukan Jumlah "); {
              delay(5000);
            }
            jumlah();
            validasi1();
          }
        }
        lcd.clear();
        lcd.print("----Welcome----");
        arrDataa[0] = "";
        return;


      }
    }
  }
  //item3
  if (digitalRead(pinButton3) == LOW) {

    Serial.println("Item 3");
    id = "3";
    Serial.println(id);
    //  kur();

    HTTPClient http;
    request_string = "http://192.168.1.7/ven/ambil.php?id=";
    request_string += id;

    Serial.print("requesting URL: ");
    Serial.print(request_string);
    // client.print(String("GET ") + request_string + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    http.begin(request_string);
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      //Serial.println("Stok Habis");
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
      int q = payload.toInt();
      Serial.println(q); //Print the response payload


      if (q <= 0) {
        mybot.sendMessage(idbot, "Soba Sold out");
        Serial.println("Sold out");
        lcd.begin();
        lcd.backlight();
        lcd.print("Sold Out"); {
          delay(2000);
        }
        lcd.clear();
        lcd.print("----Welcome----");
        return;
        http.end();   //Close connection
      }

      int value = EEPROM.read(4); //read address on eeprom

      value = (value * 1);
      Serial.print("baca stok : ");
      Serial.println(value); // show result read on eeprom
      delay(3000);

      Serial.println(value); //Print the response payload
      if (value <= 0) {
        Serial.println("Sold out");
        lcd.begin();
        lcd.backlight();
        lcd.print("Sold out"); {
          delay(2000);
        }
        lcd.clear();
        lcd.print("----Welcome----");
        return;



      }

      else if (value >= 0) {


        lcd.clear();
        lcd.print(" Masukan Jumlah ");
        Serial.print("Masukan Jumlah : "); {
          delay(7000);
        }
        jumlah();
        u = arrDataa[0];
        long u = arrDataa[0].toInt();
        if (u <= 0) {
          Serial.print("Data Kosong");
          lcd.clear();
          lcd.print("Data Kosong"); {
            delay(4000);
          }
          lcd.clear();
          lcd.print("----Welcome----");
          return;
        }

        Serial.println("Verifikasi");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Jumlah");
        lcd.setCursor(8, 0);
        lcd.print(u);
        lcd.setCursor(0, 1);
        lcd.print("*/Ya   #/Tidak"); {
          delay(7000);
        }

        String data = "";
        while (Serial.available() > 0)
        {
          data += char(Serial.read());
        }
        delay (3000);
        data.trim();


        if (data != "")
        {
          int index = 0;
          for (int i = 0; i <= data.length (); i++)
          {
            char delimiter = '&';
            if (data[i] != delimiter)
              arrDataaa[index] += data[i];
            else
              index++;
          }

          pilihan = arrDataaa[0];
          if (pilihan == '*') {
            Serial.println(pilihan);
            arrDataaa[0] = '\0';
            harga_barang = 1000;
            beli_item(harga_barang);

          }
          else if (pilihan == '#' ) {
            arrDataa[0] = "";
            arrDataaa[0] = '\0';
            Serial.print("Masukan Jumlah Lagi : ");
            lcd.clear();
            lcd.print(" Masukan Jumlah "); {
              delay(5000);
            }
            jumlah();
            validasi1();
          }
        }
        lcd.clear();
        lcd.print("----Welcome----");
        arrDataa[0] = "";
        return;


      }
    }
  }
}

void kur() {
  HTTPClient http;

  http.begin("http://192.168.1.7/ven/stok.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("id=" + id);
  if (httpResponseCode > 0) {
    Serial.println ("Sending to database, Success");
  }
  http.end();
}

void transaksi() {

  HTTPClient http;

  http.begin("http://192.168.1.7/ven/transa.php");

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("id=" + id);
  if (httpResponseCode > 0) {
    //Serial.println ("Succes");
  }
  http.end();
}

void terjual() {

  HTTPClient http;

  http.begin("http://192.168.1.7/ven/penjualanbaru.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("id=" + id);
  if (httpResponseCode > 0) {
    //Serial.println ("Succes");
  }
  http.end();
}


//*****************************************************************************************//
