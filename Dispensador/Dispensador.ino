#include <SPI.h>
#include "PN532_SPI.h"
#include "PN532.h"
#include "NfcAdapter.h"

PN532_SPI interface(SPI, 10); // create a SPI interface for the shield with the SPI CS terminal at digital pin 10

NfcAdapter nfc = NfcAdapter(interface); // create an NFC adapter object
 // include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
String rec;
char chab[20];
void setup() {
Serial.begin(115200); // start serial comm
    Serial.println("NDEF Reader");
    nfc.begin(); // begin NFC comm
      // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.write("NDEF Reader Enabled");
}

void loop() {
  if (nfc.tagPresent()) // Do an NFC scan to see if an NFC tag is present
  {
    lcd.clear();
    NfcTag tag = nfc.read();
    Serial.println(tag.getTagType());
    Serial.print("UID: ");Serial.println(tag.getUidString());
    rec=tag.getUidString();
    rec.toCharArray(chab, 12);
    lcd.setCursor(0,1);
    lcd.write("UID:");
    for(int i=0;i<=10;i++){
      lcd.write(chab[i]);
    }
    lcd.setCursor(0,0);
    lcd.write("User Registered");
  }
delay(1000);
}
