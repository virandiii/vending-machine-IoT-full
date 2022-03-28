#include <SPI.h>
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
#define EEPROM_SIZE 8

//String request_string;


int index1, index2;
String dat1, dat2;
int data1 = 0; // data
int data2 = 0; // data
int addr1  = 0; // address on eeprom
int addr2 = 0; // address on eeprom
int num1;
int num2;
int num6;
int num7;
int wifi_kom = 0;
int aaa = 0;
int bbb = 0;
String a ;
String arrData[3];


HTTPClient http;
String request_string;
const char* host = "192.168.1.9";
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

String stoks = "3";
const int pinButton = 04;
const int pinButton2 = 02;
const int pinButton3 = 05;
const int pinBuzzer = 16;

const char* ssid = "User-iPhone 12 Pro Max";
const char* pass = "bisajadi";

Servo servo;
Servo servo1;
Servo servo2;
//int httpCode;
int harga_barang;
String id;
int kurang;
//*****************************************************************************************//
void kirimtransaksisementara() {
  int item1 = EEPROM.read(1); //read address on eeprom

  item1 = (item1 * 1);
  Serial.print("jumlah transaksi : ");
  Serial.println(item1);
  if (item1 > 0) {
    for (int i = 0; i <= item1; i++) {
      Serial.println("Kirim ke database : ");
      HTTPClient http;
      int id = 1;
      http.begin("http://192.168.1.9/ven/transa.php");
      //http.begin("http://192.168.1.11/ven/penjualan.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST("id=" + id);
      if (httpResponseCode > 0) {
        //Serial.println ("Succes");
      }
      http.end();
    }
  }
  /*  int item2 = EEPROM.read(3); //read address on eeprom

    item2 = (item2 * 1);
    Serial.print("jumlah transaksi : ");
    Serial.println(item2);

    int item3 = EEPROM.read(5); //read address on eeprom

    item3 = (item3 * 1);
    Serial.print("jumlah transaksi : ");
    Serial.println(item3);


    EEPROM.write(1, 0); // save on eeprom
    EEPROM.commit(); */
}

//***************************************************************************//
void konekWifi()
{
  lcd.begin();
  lcd.backlight();
  lcd.print("Conect to Wifi..");
  WiFi.disconnect();
  Serial.println("Wifi Terputus !!!");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
    digitalWrite(2, LOW);   // Turn the LED on by making the voltage LOW
    delay(100);            // Wait for a second
    digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(100);            // Wait for two seconds
    if (bbb != 3)
    {
      bbb = bbb + 1;
    }
    milih();
  }

  //Serial.begin(9600);

  Serial.println("Connected..");
  kirimtransaksisementara();
  lcd.clear();
  lcd.print("Wifi Connected");
  lcd.clear();
  lcd.print("----Wellcome----");

  Serial.println("Connected to the WiFi network");
}
//*****************************************************************************//
void reconNetwork() {
  konekWifi();

}
//******************************************************************************//
void cekKoneksi()
{
  //cek koneksi wifi
  if (WiFi.status() != WL_CONNECTED || WiFi.status() == WL_DISCONNECTED)
  {
    Serial.println("Wifi Terputus 1");
    lcd.clear();
    lcd.print("_Disconnect_");
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
        Serial.println("Wifi WUZZ");
        wifi_kom = 2;
      }
    }
  }
}
//*************************************************************************//
void setup() {
  //----------------------SETUP LED------------------------------------------
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(6000);
  digitalWrite(2, HIGH);
  //----------------------SETUP SERIAL--------------------------------------
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  EEPROM.begin (EEPROM_SIZE);
  //----------------------SETUP KONEKSI--------------------------------------
  konekWifi();
}

String strID, val, data;
unsigned long timenow = 0;



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

void serv1() {
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

void simpen1() {
  id = "1";
  int data2 = id.toInt() ;

  int item1 = EEPROM.read(1); //read address on eeprom

  item1 = (item1 * 1);

  delay(1000);
  num2 = (item1 + 1); // separate value or time
  Serial.print("simpan jumlah transaksi : ");
  Serial.println(num2);
  EEPROM.write(1, num2); // save on eeprom
  EEPROM.commit();

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

void bacadata () {

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
      char delimiter = '#';
      if (data[i] != delimiter)
        arrData[index] += data[i];
      else
        index++;
    }

    Serial.println(arrData[0]);
    int x = arrData[0].toInt();
    int y = arrData[1].toInt();
    int z = arrData[2].toInt();

    int value5 = EEPROM.read(0); //read address on eeprom

    value5 = (value5 * 1 );
    Serial.print("Stok sebelumnya : ");
    Serial.println(value5); // show result read on eeprom
    delay(1000);

    num1 = (value5 + x); // separate value or time
    EEPROM.write(0, num1); // save on eeprom



    //*****************************************************************//
    int value6 = EEPROM.read(2); //read address on eeprom

    value6 = (value6 * 1);
    Serial.print("Stok sebelumnya : ");
    Serial.println(value6); // show result read on eeprom
    delay(1000);
    num6 = (value6 + y); // separate value or time
    EEPROM.write(2, num6); // save on eeprom


    //****************************************************************//
    int value7 = EEPROM.read(4); //read address on eeprom

    value7 = (value7 * 1);
    Serial.print("Stok sebelumnya : ");
    Serial.println(value7); // show result read on eeprom
    delay(1000);
    num7 = (value7 + z); // separate value or time
    EEPROM.write(4, num7); // save on eeprom

    EEPROM.commit();
    delay (3000);

  }
  arrData [0] = "";
  arrData [1] = "";
  arrData [2] = "";
}
void beli_item(int harga) {


  lcd.begin();
  lcd.backlight();


  if ( harga_barang == 3000) {



    lcd.setCursor(0, 0);
    lcd.print("----Tap Kartu---");
    lcd.setCursor(0, 1);
    lcd.print("Cheetos");
    lcd.setCursor(7, 1);
    lcd.print("Rp.");
    lcd.setCursor(10, 1);
    lcd.print(harga_barang); {
      delay(2000);
    }
    lcd.clear();
    lcd.print("--Please  Wait--"); {
      delay(2000);
    }
    lcd.clear();


  }


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
  bepp1();
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

  //---------------------------------------- GET LAST NAME

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

  //------------------BACA-------------------------------
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



  //---------------- WRITE-------------------------------
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

      num1 = value - 1;
      Serial.print("sisa stok : ");
      Serial.println(num1); // show result read on eeprom
      EEPROM.write(0, num1);
      EEPROM.commit();

      cek();

      serv1();
    }

    if (b == 2000) {

      Serial.println("Please Take");
      int value = EEPROM.read(2); //read address on eeprom

      value = (value * 1);
      Serial.print("baca stokkk : ");
      Serial.println(value); // show result read on eeprom
      delay(1000);

      num7 = value - 1;
      EEPROM.write(2, num7);
      EEPROM.commit();


      value = EEPROM.read(2); //read address on eeprom

      value = (value * 1);
      Serial.print("sisa stok : ");
      Serial.println(value); // show result read on eeprom
      delay(1000);
      serv2();

    }

    if (b == 1000) {
      Serial.println("Please Take");
      int value = EEPROM.read(4); //read address on eeprom

      value = (value * 1);
      Serial.print("baca stokkk : ");
      Serial.println(value); // show result read on eeprom
      delay(1000);

      num7 = value - 1;
      EEPROM.write(4, num7);
      EEPROM.commit();


      value = EEPROM.read(4); //read address on eeprom

      value = (value * 1);
      Serial.print("sisa stok : ");
      Serial.println(value); // show result read on eeprom
      delay(1000);
      serv3();
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
    lcd.print("----Wellcome----");

  }


  else if (a < b)
  {
    lcd.begin();
    lcd.backlight();
    lcd.print("Saldo Kurang!!!"); {
      delay(2000);
    }
    lcd.clear();
    lcd.print("----Wellcome----");

    Serial.println("Less Balance ");
  }
  //------------------------------------------------------

  Serial.println("\n**End Reading**\n");
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}



//*****************************************************************************************//
void loop() {

  bacadata();

  int value5 = EEPROM.read(0); //read address on eeprom

  value5 = (value5 * 1);
  Serial.print("baca stok : ");
  Serial.println(value5); // show result read on eeprom

  int value6 = EEPROM.read(2); //read address on eeprom

  value6 = (value6 * 1);
  Serial.print("baca stok : ");
  Serial.println(value6); // show result read on eeprom

  int value7 = EEPROM.read(4); //read address on eeprom

  value7 = (value7 * 1);
  Serial.print("baca stok : ");
  Serial.println(value7); // show result read on eeprom
  delay(3000);

  cekKoneksi();
  milih2();


}

//*****PEMBELIAN OFFLINE*****//
void milih () {


  //item1
  if (digitalRead(pinButton) == LOW) {

    Serial.println("Item 3");
    id = "1";
    Serial.println(id);
    //  kur();
    bepp();
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
      lcd.print("----Wellcome----");
      return;



    }

    else if (value >= 0) {
      harga_barang = 3000;
      beli_item(harga_barang);


    }
  }
  //item2
  if (digitalRead(pinButton2) == LOW) {

    Serial.println("Item 2");
    id = "2";
    Serial.println(id);
    //  kur();
    bepp();
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
      lcd.print("----Wellcome----");
      return;



    }

    else if (value >= 0) {

      harga_barang = 2000;
      beli_item(harga_barang);


    }
  }
  //item3
  if (digitalRead(pinButton3) == LOW) {

    Serial.println("Item 3");
    id = "3";
    Serial.println(id);
    //  kur();
    bepp();
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
      lcd.print("----Wellcome----");
      return;



    }

    else if (value >= 0) {
      harga_barang = 1000;
      beli_item(harga_barang);


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
    //  kur();
    bepp();
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
      lcd.print("----Wellcome----");
      return;



    }

    else if (value >= 0) {
      harga_barang = 3000;
      beli_item(harga_barang);


    }
  }
  //item2
  if (digitalRead(pinButton2) == LOW) {

    Serial.println("Item 2");
    id = "2";
    Serial.println(id);
    //  kur();
    bepp();
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
      lcd.print("----Wellcome----");
      return;



    }

    else if (value >= 0) {

      harga_barang = 2000;
      beli_item(harga_barang);


    }
  }
  //item3
  if (digitalRead(pinButton3) == LOW) {

    Serial.println("Item 3");
    id = "3";
    Serial.println(id);
    //  kur();
    bepp();
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
      lcd.print("----Wellcome----");
      return;



    }

    else if (value >= 0) {
      harga_barang = 1000;
      beli_item(harga_barang);


    }
  }
}
