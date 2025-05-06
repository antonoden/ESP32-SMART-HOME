#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ElegantOTA.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

unsigned long int ota_progress_millis = 0;

void onOTAStart() {
    // Log when OTA has started
    Serial.println("OTA update started!");
    // <Add your own code here>
  }
  
  void onOTAProgress(size_t current, size_t final) {
    // Log every 1 second
    if (millis() - ota_progress_millis > 1000) {
      ota_progress_millis = millis();
      Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
    }
  }
  
  void onOTAEnd(bool success) {
    // Log when OTA has finished
    if (success) {
      Serial.println("OTA update finished successfully!");
    } else {
      Serial.println("There was an error during OTA update!");
    }
    // <Add your own code here>
  }

  const char* model_number_to_string(esp_chip_model_t model) {
    switch (model) {
        case CHIP_ESP32: return "ESP32";
        case CHIP_ESP32S2: return "ESP32-S2";
        case CHIP_ESP32S3: return "ESP32-S3";
        case CHIP_ESP32C3: return "ESP32-C3";
        case CHIP_ESP32H2: return "ESP32-H2";
    }
    return "No model detected";
  }

  void init_OTA () {

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info); 
    String indexPage = String(R"rawliteral(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>ESP32 Hardware Info</title>
            <style>
                body { font-family: Arial, sans-serif; text-align: center; padding: 20px; }
                table { margin: auto; width: 60%; border-collapse: collapse; }
                th, td { border: 1px solid #ddd; padding: 10px; }
                th { background-color: #4CAF50; color: white; }
                tr:nth-child(even) { background-color: #f2f2f2; }
            </style>
        </head>
        <body>
            <h2>ESP32 Hardware Info</h2>
            <button onclick="window.location.href='/update'" style="
                background-color: #4CAF50;
                border: none;
                color: white;
                padding: 12px 20px;
                font-size: 16px;
                cursor: pointer;
                border-radius: 5px;">
                🔄 Update Firmware
            </button>
            <table>
                <tr><th>Property</th><th>Value</th></tr>

                <tr><td>Chip Model</td><td>)rawliteral") + 
                String(model_number_to_string(chip_info.model)) + 
                String(R"rawliteral(</td></tr>

                <tr><td>Cores</td><td>)rawliteral") + 
                String(chip_info.cores) + 
                String(R"rawliteral(</td></tr>

                <tr><td>Revision</td><td>)rawliteral") + 
                String(chip_info.revision) + 
                String(R"rawliteral(</td></tr>

                <tr><td>Features</td><td>)rawliteral") + 
                chip_info.features + 
                String(R"rawliteral(</td></tr>

                <tr><td>Flash Size</td><td>)rawliteral") + 
                String(spi_flash_get_chip_size() / (1024 * 1024)) + 
                String(R"rawliteral( MB</td></tr>

                <tr><td>Free heap size</td><td>)rawliteral") + 
                String(esp_get_free_heap_size()/ 1024)  + 
                String(R"rawliteral( kB</td></tr>

                <tr><td>IDF-VERSION (IoT Development Framework)</td><td>)rawliteral") + 
                String(esp_get_idf_version())  + 
                String(R"rawliteral( kB</td></tr>

                <tr><td>Autoconnect enabled</td><td>)rawliteral") + 
                String(esp_get_idf_version())  + 
                String(R"rawliteral( kB</td></tr>

                <tr><td>Time since boot</td><td id="timestamp">)rawliteral") + 
                String(esp_timer_get_time() / 1000 / 1000) + 
                String(R"rawliteral( seconds</td></tr>
               
            </table>

            <script>

                function updateTimestamp() {
                    fetch('/timestamp')  // Call the server endpoint
                        .then(response => response.text())  // Get response as text
                        .then(data => {
                            document.getElementById('timestamp').innerText = data;
                        })
                        .catch(error => console.error("Error fetching timestamp:", error));
                }

                // Refresh timestamp
                setInterval(updateTimestamp, 5000);
                updateTimestamp(); // Call immediately on page load
            </script>
        </body>
        </html>
    )rawliteral");

    server.on("/", HTTP_GET, [indexPage](AsyncWebServerRequest *request) {
        request->send(200, "text/html", indexPage); });
    
      ElegantOTA.begin(&server);    // Start ElegantOTA
      // ElegantOTA callbacks
      ElegantOTA.onStart(onOTAStart);
      ElegantOTA.onProgress(onOTAProgress);
      ElegantOTA.onEnd(onOTAEnd);
    
      server.begin();
    }

void async_loop_OTA() {
    delay(500);
    server.on("/timestamp", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(200, "text/plain", String(esp_timer_get_time() / 1000 / 1000) + " seconds");
    });
    ElegantOTA.loop();
}

