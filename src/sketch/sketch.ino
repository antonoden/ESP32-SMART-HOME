#include "driver.h"
#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  delay(2000); // delay needed for messages on serial is to be read or written correctly
  main();
  Serial.println("Wifi setup done");
}

void loop() {
  
}
