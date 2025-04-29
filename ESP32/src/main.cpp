#include <Arduino.h>
#include <iostream>
#include "WiFi.h"

// functions for debugging and constant to allow debuging functions to be called
#include "debug.h"
#define DEBUG 1

int main () {
    if(DEBUG) in("main");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    int numNetworks;
    if((numNetworks = WiFi.scanNetworks()) > 0) {
        std::cout << "Found networks" << std::endl;
    } else {
        std::cout << "Didn't find any networks" << std::endl;
    }
    if(DEBUG) out("main");
    return 0;
}

/* IS GOING TO BE RUNNED ONCE ON STARTUP */
void setup() {
  Serial.begin(115200);
  delay(2000); // delay needed for messages on serial is to be read or written correctly
  main();
  Serial.println("Wifi setup done");
}

/* ENDLESS LOOP REST OF LIFE */
void loop() {
  delay(50000);
  
}