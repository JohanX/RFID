#include <Arduino.h>
#include <BNBRFID.h>
#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define CARD_BYTES      4          // Number of bytes the card holds
BNBRFID rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance

byte validUID[][4] = {
        {0x14, 0x4D, 0xE5, 0x6A},
        {0x93, 0xB6, 0x98, 0xAC},
};

bool checkValidUID(byte *uid) {
    for (byte i = 0; i < (sizeof(validUID) / sizeof(*validUID)); i++) {
        int validBytes = 0;
        for (byte j = 0; j < CARD_BYTES; j++) {
            validBytes += (int) validUID[i][j] == uid[j];
        }
        if (validBytes == CARD_BYTES) {
            return true;
        }
    }
    return false;
}

void printCardUID(byte uid[]) {
    Serial.print(F("Card UID:"));
    for (byte i = 0; i < CARD_BYTES; i++) {
        if (uid[i] < 0x10)
            Serial.print(F(" 0"));
        else
            Serial.print(F(" "));
        Serial.print(uid[i], HEX);
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);   // Initialize serial communications with the PC
    rfid.init();
    Serial.println(F("Please scan card"));
}

void loop() {
    uint8_t *uid = rfid.readCard();
    if (uid != NULL) {
        printCardUID(uid);
        if (checkValidUID(uid)) {
            Serial.println(F("Valid Card!"));
        }
    }
}

