#include <SPI.h>
#include <MFRC522.h>

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define RST_PIN         9           
#define SS_PIN          10          

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

char stringAngka[17];
int indexKeypad = 0;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2);

int stt_isi = 0;
//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read

  lcd.begin();
  lcd.backlight();
  SPI.begin();
  lcd.print("Ready");
}

//*****************************************************************************************//
void loop() {
 
  keypaddd();
  


}
//*****************************************************************************************//

void keypaddd()
{
   char keys = keypad.getKey();
  if (keys) {
    //    Serial.println(keys);
    switch (keys)
    {
      case '0'...'9':
        //    first = first * 10 + (indexKeypad - '0');
        if (!indexKeypad)
        {
          lcd.clear();
        }
        stringAngka [indexKeypad++] = keys;
        lcd.print(keys);
        Serial.println(keys);
        return;
  
      case '*'://reset
        
        lcd.clear();
        lcd.print("Input Angka");
        indexKeypad = 0;
        break;

      case '#':
        
        Serial.println("Top-Up");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mengisi Saldo");
        lcd.setCursor(0, 1);
        lcd.print("Rp.");
        lcd.setCursor(2, 1);
        lcd.print(stringAngka); {
          delay(2000);
        }
        lcd.clear();
        Serial.println(stringAngka);
    
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tap Kartu");
        stt_isi = 1;
        delay(1000);
        String a = String(stringAngka);      
        long b = a.toInt(); 
        tambahSaldo(b);
        
    }
  }  
}



void tambahSaldo(long harga)
{
  stt_isi = 0;
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
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

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------
  

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F("Name: "));

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

  //PRINT FIRST NAME
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
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i]);
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
  long a = hasil.toInt();
  long b = harga;
  long c = a + b;
  Serial.print("Current Balance : ");
  Serial.println(c);


  
  
  //---------------- WRITE-------------------------------

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
    else Serial.println(F("MIFARE_Write() success: "));

  Serial.println(F("\n**End Reading**\n"));
  delay(1000); //change value if you want to read cards faster
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rp " + String(a));
  lcd.setCursor(0,1);
  lcd.print("+ " + String(b));
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Saldo Sekarang : ");
  lcd.setCursor(0,1);
  lcd.print(String(c));
}

void bacaSaldo()
{
    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
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

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

Serial.print(F("Name: "));

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

  //PRINT FIRST NAME
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
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i]);
    tampung[i] = buffer2[i];
  }



  //------------------BACA-------------------------------
  String stampung = String(tampung);
  int firstIndex = stampung.indexOf('<');
  int lastIndex = stampung.indexOf('>');
  String hasil = stampung.substring(firstIndex + 1, lastIndex);
  Serial.println("--------------------------");
  Serial.print("BALANCE : ");
  Serial.println(hasil);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Balance");
  lcd.setCursor(0, 1);
  lcd.print(hasil);
  
  Serial.println(F("\n**End Reading**\n"));
  delay(1000); //change value if you want to read cards faster
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
