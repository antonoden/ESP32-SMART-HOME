#include <WiFiManager.h>

WiFiManager wifiManager;

// Static IP configuration
IPAddress _ip = IPAddress(192, 168, 1, 117);
IPAddress _gw = IPAddress(192, 168, 1, 1);
IPAddress _sn = IPAddress(255, 255, 255, 0);

bool wifiConnect() {
    
    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    //wifiManager.resetSettings();

    wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);
    wifiManager.setTitle("ESPDEV");
    wifiManager.setDarkMode(true);

    //tries to connect to last known settings
    //if it does not connect it starts an access point with the specified name
    //and goes into a blocking loop awaiting configuration
    if(!wifiManager.autoConnect("AP_WIFICONFIG_ESP32")) {
      Serial.println("failed to connect, we restarting device");
      delay(3000);
      ESP.restart();
      delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    Serial.println("local ip");
    Serial.println(WiFi.localIP()); // Print the ESP32 IP address to Serial Monitor

    return true;
}

bool isConnected() {
  if(wifiManager.getWLStatusString() = WL_CONNECTED) {
    return true;
  } 
  return false;
}