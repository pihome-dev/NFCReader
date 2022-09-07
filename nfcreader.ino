struct keyTagsStruct  { byte id0; byte id1; byte id2; byte id3; int en; int mode; };
struct keyTagsStruct keyTagID[20];

#include "nfcreader.h"

#define SS_PIN 10
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);

  init_eeprom();
  Serial.println("EEPROM initialisiert");
  
  SPI.begin(); // init SPI bus
  Serial.println("SPI initialisiert");
  
  rfid.PCD_Init(); // init MFRC522
  Serial.println("MFRC522 initialisiert");

  Serial.println("RFID/NFC Reader ready");
  Serial.println("Tap RFID/NFC Tag on reader");

  keyTagID[0].id0 = 0xB6;
  keyTagID[0].id1 = 0x1C;
  keyTagID[0].id2 = 0x80;
  keyTagID[0].id3 = 0x4D;
  keyTagID[0].en = 1;
  keyTagID[0].mode = 1;

  keyTagID[1].id0 = 0x23;
  keyTagID[1].id1 = 0xE1;
  keyTagID[1].id2 = 0xA5;
  keyTagID[1].id3 = 0x94;
  keyTagID[1].en = 1;
  keyTagID[1].mode = 1;
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      boolean granted = false;

      for (int i=0; i<TAGS_COUNT; i++) {
        if (rfid.uid.uidByte[0] == keyTagID[i].id0 &&
          rfid.uid.uidByte[1] == keyTagID[i].id1 &&
          rfid.uid.uidByte[2] == keyTagID[i].id2 &&
          rfid.uid.uidByte[3] == keyTagID[i].id3 ) {
            granted = true;
            Serial.println("Access is granted");
            Serial.print("UID:");
            for (int i = 0; i < rfid.uid.size; i++) {
              Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
              Serial.print(rfid.uid.uidByte[i], HEX);
            }
            Serial.println();
            break;
          }
      }

      if (granted == false) {
        Serial.print("Access denied for user with UID:");
        for (int i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
      }

      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }
}
