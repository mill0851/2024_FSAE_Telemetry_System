#include <SPI.h>
#include <SD.h>

const int chipSelect = SDCARD_SS_PIN;
String HEADER = "Time(milli),pot1,pot2,pot3,pot4";


void setup() {

  // SERIAL COMMUNICATION WITH COMPUTER
  Serial.begin(9600);

  // WAIT FOR CONNECTION
  while(!Serial) {
    ;
  }

  // SERIAL COMMUNICATION WITH HC-12
  Serial1.begin(9600);

  // WAIT FOR CONNECTION
  while (!Serial1) {
    ;
  }

  delay(500);

  // INITIALIZE SD CARD CONNECTION
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Initialization Failed");
    return;
  }
  // Serial.println("SD Initialization Complete");

  delay(500);

  // OPEN/CREATE DATA FILE
  File dataFile = SD.open("data.csv", FILE_WRITE);

  // IF THE DATA FILE OPENED WRITE THE HEADER, IF NOT SEND ERROR MESSAGE
  if (dataFile) {
    // Serial.println("data.csv opened...");
    // Serial.println("Writing header to data.csv...");
    dataFile.println(HEADER);
    dataFile.close();
  }
  else {
    Serial.println("Error opening data.csv");
  }

  delay(500);
}

void loop() {

  // OPEN DATA FILE
  File dataFile = SD.open("data.csv", FILE_WRITE);

  if (dataFile) {
    String data = readData();

    if (data.length() > 0) {
      dataFile.print(data);
      Serial.print(data);
      dataFile.close();
    }
    else {
      dataFile.close();
    }
  }
  else {
    Serial.println("Error opening data.csv in loop");
  }
  delay(1000);
}

// TRANSMITS AND RECIEVES DATA THROUGH THE HC-12 MODULE
String readData () {
  String data = "";
  
  // WHILE SERIAL1 (THE RADIO MODULE) HAS DATA IN ITS BUFFER
  while (Serial1.available()) {
    
    // READ IN NEXT CHAR FROM SERIAL1
    char receivedChar = Serial1.read();
    
    // APPEND THE DATA STRING
    data += receivedChar;
  }

  return data;
}