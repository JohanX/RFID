#include "BNBRFID.h"

/**
 * Constructor for configurable pins
 */
BNBRFID::BNBRFID(uint8_t ss = SS_PIN, uint8_t rst = RST_PIN) {
    reader = MFRC522(ss, rst);
}

/**
 * Init SPI and MFRC522
 */
void BNBRFID::init() {
    SPI.begin();      // Init SPI bus
    reader.PCD_Init();   // Init MFRC522
}

/**
 * Read card and return UID
 */
uint8_t *BNBRFID::readCard() {
    if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
        reader.PICC_HaltA();
        return reader.uid.uidByte;
    }
    return NULL;
}