#include <WiFiManager.h>

WiFiManager wifiManager;

// Static IP configuration
IPAddress _ip = IPAddress(10, 0, 1, 78);
IPAddress _gw = IPAddress(10, 0, 1, 1);
IPAddress _sn = IPAddress(255, 255, 255, 0);

static bool wifiConnect() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi ..");
    for(int i=0; (WiFi.status() != WL_CONNECTED) || i>10; i++) {
      Serial.print('.');
      delay(3000);
    }

    if(!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("Failed to configure Static IP");
    } else {
        Serial.println("Static IP configured!");
    }
    
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());  // Print the ESP32 IP address to Serial Monitor

    return true;
}

bool wifiInit() {
    int numFoundNetworks;
    if((numFoundNetworks = WiFi.scanNetworks()) > 0) {
      Serial.print("Found ");
      Serial.print(numFoundNetworks);
      Serial.println(" available networks as follows...");
      for(int i = 0; i<numFoundNetworks; i++) {
        Serial.print("SSID:");
        Serial.println(WiFi.SSID(i));
        Serial.print("RSSI: ");
        Serial.println(WiFi.RSSI(i));
        Serial.print("Encryption type: ");
        Serial.println(WiFi.encryptionType(i));
      } 
      Serial.print("Attempting connection to SSID: ");
      Serial.println(ssid);
      if(wifiConnect()) {
        Serial.println("Successfully connected to:");
        Serial.println(ssid);
      }
      else {
        Serial.println("Unable to connect to:");
        Serial.println(ssid);
      }
    } 
    else {
      Serial.println("Didn't find any SSIDs while scanning...:");
      return false;
    }
    return true;
}

bool wifiConnected() {
    if(WiFi.status() != WL_CONNECTED)
      return false;
    return true;
}