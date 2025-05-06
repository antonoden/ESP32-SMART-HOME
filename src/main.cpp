#include "network.h"
#include "mqtt.h"
#include "OTAupdate.h"
#include <Arduino.h>

// Connected PINS names
int pushButton = 4;
int builtinLED = 2;
/* IS GOING TO BE RUNNED ONCE ON STARTUP */
void setup() {
  Serial.begin(115200);

  delay(2000); // delay needed for messages on serial is to be read or written correctly
  pinMode(builtinLED, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(pushButton, INPUT);
  digitalWrite(builtinLED, LOW);
  if(wifiConnect()) {  // Showing on LED that wifi connection has been established
    digitalWrite(builtinLED, HIGH);
  } 

  delay(2000);
  //mqtt_init();

  init_OTA();
}

/* ENDLESS LOOP REST OF LIFE */
void loop() {
  async_loop_OTA();
}