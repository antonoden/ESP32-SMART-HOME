#include <WiFi.h>
#include "network.h"
#include <Arduino.h>

// Connected PINS names
int pushButton = 4;
int builtinLED = 2;
int BLUELED = 19;
/* IS GOING TO BE RUNNED ONCE ON STARTUP */
void setup() {
  Serial.begin(115200);
  delay(2000); // delay needed for messages on serial is to be read or written correctly
  pinMode(builtinLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(pushButton, INPUT);
  if(wifiInit()) {  // Showing on LED that wifi connection has been established
    digitalWrite(builtinLED, HIGH);
  } else {
    digitalWrite(builtinLED, LOW);
  }
}

/* ENDLESS LOOP REST OF LIFE */
boolean buttonpushed = false;

void loop() {
  delay(2000);
  if(digitalRead(pushButton)) {
    if(buttonpushed) {
      digitalWrite(BLUELED, HIGH);
      buttonpushed = false;
    } else {
      digitalWrite(BLUELED, LOW);
      buttonpushed = true;
    }
  }
  if(!wifiConnected()) {
    digitalWrite(builtinLED, LOW);
    WiFi.reconnect();
  }
}