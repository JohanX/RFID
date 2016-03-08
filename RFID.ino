#include <SoftwareSerial.h>

int RFIDResetPin = 13;

// software serial #1: TX = digital pin 10, RX = digital pin 11
SoftwareSerial rfid(2, 3);

void setup(){
  Serial.begin(9600);
  rfid.begin(9600);
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);
}

void loop(){

  char tagString[13];
  int index = 0;
  boolean reading = false;

  while(rfid.available()){

    int readByte = rfid.read(); //read next available byte

    if(readByte == 2) reading = true; //begining of tag
    if(readByte == 3) reading = false; //end of tag

    if(reading && readByte != 2 && readByte != 10 && readByte != 13){
      //store the tag
      tagString[index] = readByte;
      index ++;
    }
  }

  checkTag(tagString); //Check if it is a match
  clearTag(tagString); //Clear the char of all value
  resetReader(); //reset the RFID reader
}

void printTag(char tag[]){
    Serial.print("Read tag: ");
    Serial.println(tag); //read out any unknown tag
}

void resetReader(){
///////////////////////////////////
//Reset the RFID reader to read again.
///////////////////////////////////
  digitalWrite(RFIDResetPin, LOW);
  digitalWrite(RFIDResetPin, HIGH);
  delay(150);
}

void clearTag(char one[]){
///////////////////////////////////
//clear the char array by filling with null - ASCII 0
//Will think same tag has been read otherwise
///////////////////////////////////
  for(int i = 0; i < strlen(one); i++){
    one[i] = 0;
  }
}

