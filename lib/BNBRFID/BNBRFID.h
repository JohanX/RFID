#include <MFRC522.h>

#ifndef RFID_BNBRFID_H
#define RFID_BNBRFID_H


class BNBRFID {
public:
    void init();

    uint8_t *readCard();

    BNBRFID(uint8_t SS_PIN, uint8_t RST_PIN);

private:
    static const byte SS_PIN = 9;
    static const byte RST_PIN = 10;
    MFRC522 reader;
};

#endif //RFID_BNBRFID_H
