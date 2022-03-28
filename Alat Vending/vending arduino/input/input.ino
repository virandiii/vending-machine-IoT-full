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
Serial.println("*");

        break;

      case '#':

        Serial.println("#");
      

    }
  }
}
