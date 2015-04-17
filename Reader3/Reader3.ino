#include <SPI.h>
#include "PN532_SPI.h"
#include "PN532.h"
#include "NfcAdapter.h"

PN532_SPI interface(SPI, 10); // create a SPI interface for the shield with the SPI CS terminal at digital pin 10

NfcAdapter nfc = NfcAdapter(interface); // create an NFC adapter object
 
void setup() {
Serial.begin(9600);
Serial.println("NDEF Reader");
nfc.begin();
}
void loop() {
Serial.println("\nScan a NFC tag\n");
if (nfc.tagPresent()) {
NfcTag tag = nfc.read();
Serial.println(tag.getTagType());
Serial.print("UID: ");
Serial.println(tag.getUidString());
if (tag.hasNdefMessage()) { // every tag won't have a message
NdefMessage message = tag.getNdefMessage();
Serial.print("\nThis NFC Tag contains an NDEF Message with ");
Serial.print(message.getRecordCount());
Serial.print(" NDEF Record");
if (message.getRecordCount() != 1) {
// if there's more than one record, pluralize:
Serial.print("s");
}
// cycle through the records, printing some info from each
int recordCount = message.getRecordCount();
for (int i = 0; i < recordCount; i++)
{
Serial.print("\nNDEF Record ");
Serial.println(i+1);
NdefRecord record = message.getRecord(i);
Serial.print(" TNF: ");
Serial.println(record.getTnf());
Serial.print(" Type: ");
Serial.println(record.getType()); // will be "" for TNF_EMPTY
// The TNF and Type should be used to determine
// how your application processes the payload
// There's no generic processing for the payload.
// it's returned as a byte[]
int payloadLength = record.getPayloadLength();
byte payload[payloadLength];
record.getPayload(payload);
// Force the data into a String:
String payloadAsString = "";
for (int c = 0; c < payloadLength; c++) {
payloadAsString += (char)payload[c];
}
Serial.print(" Payload (as String): ");
Serial.println(payloadAsString);
// id is probably blank and will return ""
String uid = record.getId();
if (uid != "") {
Serial.print(" ID: ");Serial.println(uid);
}
}
}
}
delay(3000); // delay before next read
}
