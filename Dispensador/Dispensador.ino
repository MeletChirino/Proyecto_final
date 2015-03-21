//Ayuda http://don.github.io/slides/2013-05-18-arduino-nfc/#/32
#include <SPI.h>
#include "PN532_SPI.h"
#include "PN532.h"
#include "NfcAdapter.h"

PN532_SPI interface(SPI, 10); // create a SPI interface for the shield with the SPI CS terminal at digital pin 10

NfcAdapter nfc = NfcAdapter(interface); // create an NFC adapter object
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 8);
String rec, mes;
String payloadAsString;
char chab[20];
int l, navi = 8, enter = 13, i;
void setup() {
  Serial.begin(115200); // start serial comm
  Serial.println("NDEF Reader");
  nfc.begin(); // begin NFC comm
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.write("NDEF Reader Enabled");
  attachInterrupt(0, nvi, RISING);
}
bool pro = true, por= false;
void loop() {
  if (nfc.tagPresent() && pro) // Do an NFC scan to see if an NFC tag is present
  {
    lcd.clear();
    NfcTag tag = nfc.read();
    // Serial.println(tag.getTagType());
    Serial.print("UID: "); Serial.println(tag.getUidString());
    rec = tag.getUidString();
    /*rec.toCharArray(chab, 12);
    lcd.setCursor(0, 1);
    lcd.write("UID:");
    for (int i = 0; i <= 10; i++) {
      lcd.write(chab[i]);
    }*/
    NdefMessage message = tag.getNdefMessage();
    for (int i = 0; i < message.getRecordCount(); i++)
    {

      NdefRecord record = message.getRecord(i);
      int payloadLength = record.getPayloadLength();
      byte payload[payloadLength];
      record.getPayload(payload);
      // Force the data into a String:

      payloadAsString = "";
      for (int c = 0; c < payloadLength; c++) {
        payloadAsString += (char)payload[c];
      }
      //Serial.print(" Payload (as String): ");
      //Serial.println(payloadAsString);

    }
    lcd.setCursor(0, 0);
    Serial.println(payloadAsString);
    l = payloadAsString.length();
    char chab[l];
    Serial.println(l);
    payloadAsString.toCharArray(chab, l);
    for (int i = 3; i <= l; i++) {
      lcd.write(chab[i]);
      Serial.print(chab[i]);
    } Serial.write("\n");
    pro = false;
    por= true;
    lcd.write("Que desea comprar?");
  }
 // delay(5000);
  
  if (por)
 { 
  lcd.setCursor(0, 0);
  
 }
}
void nvi()
{
  
  if (i == 4) {
    i = 0;
  } else {
    i = i + 1;
  }
switch (i)
  {
    case 0:
      lcd.clear();
      lcd.print("Almuerzo Estudiantil");
      Serial.println("Almuerzo Estudiantil");
      lcd.setCursor(0, 1);
      lcd.print("$3600");
      break;
    case 1:
      lcd.clear();
      lcd.print("Almuerzo Corriente");
      Serial.println("Almuerzo Corriente");
      lcd.setCursor(0, 1);
      lcd.print("$5600");
      break;
    case 2:
      lcd.clear();
      lcd.print("Almuerzo Seco");
      Serial.println("Almuerzo Corriente Seco");
      lcd.setCursor(0, 1);
      lcd.print("$5300");
      break;
    case 3:
      lcd.clear();
      lcd.print("Jugo pequeno");
      Serial.println("Jugo small");
      lcd.setCursor(0, 1);
      lcd.print("$1600");
      break;
    case 4:
      lcd.clear();
      lcd.print("Jugo grande");
      Serial.println("Jugo grande");
      lcd.setCursor(0, 1);
      lcd.print("$2000");
      break;
  }
}

/*
  switch (i)
  {
    case 0:
      lcd.clear();
      lcd.print("Almuerzo Estudiantil");
      Serial.println("Almuerzo Estudiantil");
      lcd.setCursor(0, 1);
      lcd.print("$3600");
      break;
    case 1:
      lcd.clear();
      lcd.print("Almuerzo Corriente");
      Serial.println("Almuerzo Corriente");
      lcd.setCursor(0, 1);
      lcd.print("$5600");
      break;
    case 2:
      lcd.clear();
      lcd.print("Almuerzo Corriente Seco");
      Serial.println("Almuerzo Corriente Seco");
      lcd.setCursor(0, 1);
      lcd.print("$5300");
      break;
    case 3:
      lcd.clear();
      lcd.print("Jugo pequeño");
      Serial.println("Jugo pequeño");
      lcd.setCursor(0, 1);
      lcd.print("$1600");
      break;
    case 4:
      lcd.clear();
      lcd.print("Jugo grande");
      Serial.println("Jugo grande");
      lcd.setCursor(0, 1);
      lcd.print("$2000");
      break;
  }*/
