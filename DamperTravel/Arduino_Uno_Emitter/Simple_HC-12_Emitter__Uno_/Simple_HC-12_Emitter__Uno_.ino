#include <SoftwareSerial.h>

// HC-12 SERIAL PORT INSTANTIATION
SoftwareSerial HC12(2, 3); // HC-12 TX Pin, HC-12 RX Pin

// ANALOG INPUT PINS 
const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;
const int potPin4 = A3;

// Digital Pins
const int LED1 = 5;
const int LED2 = 4;
const int startPin = 6;
const int stopPin = 7;

// VARIABLES
int PotFR;
int PotRR;
int PotRL;
int PotFL;
String data;
unsigned long duration;
bool collectData = false;


// COLLECTS DATA FOR THE ANLOG INPUTS THAT REPRESENT THE POTENTIOMETERS
String collectPotData() {

  // READ ANALOG INPUTS
  PotFR = analogRead(potPin1);
  PotRR = analogRead(potPin2);
  PotRL = analogRead(potPin3);
  PotFL = analogRead(potPin4);

  // RECORD TIME
  duration = millis();

  // FORMAT STRING SO THAT THE RECIEVER CAN EASILY MAKE A CSV
  data = String(duration) + "," + String(PotFR) + "," + String(PotRR) + "," + String(PotRL) + "," + String(PotFL);
  Serial.println(data);
  return (data);
}

// TRANSMITS DATA THROUGH THE HC-12 MODULE
void sendData(String data) {
  if (data.length() > 0) {
    HC12.println(data); // Send data via HC-12
    delay(10);
  }
}

// CONTROLS WHETHER TO COLLECT DATA OR NOT
void readButtons() {
  if (digitalRead(startPin) == HIGH) {
    collectData = true;
    Serial.println("beginning data collection...");
    //HC12.println("beginning data collection");
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    delay(5000); // Debounce delay
  }
  if (digitalRead(stopPin) == HIGH) {
    collectData = false;
    Serial.println("ending data collection...");
    //HC12.println("ending data collection");
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH);
    delay(5000); // Debounce delay
  }
}

// SETUP FUNCTION (THIS RUNS ONLY ONCE)
void setup() {
  Serial.begin(9600);            
  HC12.begin(9600);

  pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
}

// PROGRAM LOOP (THIS RUNS UNTIL THE ARDUINO TURNS OFF)
void loop() {
  readButtons();
  if (collectData) {
    data = collectPotData();
    Serial.println(data);
    sendData(data);
  }
  delay(100);
}


