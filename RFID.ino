#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool checkValidUID(MFRC522::Uid *uid);

byte validUID[][4] = {
    {0x14, 0x4D, 0xE5, 0x6A},
    {0x93, 0xB6, 0x98, 0xAC},
};

bool checkValidUID(MFRC522::Uid *uid) {
    for(byte i=0;i<(sizeof(validUID)/sizeof(*validUID));i++) {
        int validBytes = 0;
        for(byte j=0; j<4; j++) {
            validBytes += (int) validUID[i][j] == uid->uidByte[j];
        }
        if(validBytes == 4) {
            return true;
        }
    }
    return false;
}
void printCardUID(MFRC522::Uid *uid) {
    Serial.print(F("Card UID:"));
    for (byte i = 0; i < uid->size; i++) {
        if(uid->uidByte[i] < 0x10)
            Serial.print(F(" 0"));
        else
            Serial.print(F(" "));
        Serial.print(uid->uidByte[i], HEX);
    }
    Serial.println();
}
void setup() {
    Serial.begin(9600);   // Initialize serial communications with the PC
    SPI.begin();      // Init SPI bus
    mfrc522.PCD_Init();   // Init MFRC522
    Serial.println(F("Please scan card"));
}

void loop() {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        printCardUID(&mfrc522.uid);
        if(checkValidUID(&mfrc522.uid)){
            Serial.println(F("Valid Card!"));
        }
        mfrc522.PICC_HaltA();
    }
}

