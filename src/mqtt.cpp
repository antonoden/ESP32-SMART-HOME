#include "mqtt_client.h"
#include <Arduino.h>

const char* mqtt_server = "192.168.1.216";

static void mqtt_event_handler(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client = event->client;

    if(event->event_id == MQTT_EVENT_CONNECTED) {
        Serial.println("MQTT EVENT CONNECTED");
        esp_mqtt_client_subscribe(client, "HelloESP", 0);
        Serial.println("SENT SUBSCRIBE SUCCESSFUL");
    }
    else if(event->event_id == MQTT_EVENT_DISCONNECTED)
    {
        Serial.println("MQTT_EVENT_DISCONNECTED");
    }
    else if(event->event_id == MQTT_EVENT_SUBSCRIBED)
    {   Serial.println("MQTT_EVENT_SUBSCRIBED");
    }
    else if(event->event_id == MQTT_EVENT_UNSUBSCRIBED) //when subscribed
    {
        Serial.println("MQTT_EVENT_UNSUBSCRIBED");
    }
    else if(event->event_id == MQTT_EVENT_DATA)//when unsubscribed
    {
        Serial.println("MQTT_EVENT_DATA");
    }
    else if(event->event_id == MQTT_EVENT_ERROR)//when any error
    {
        Serial.println("MQTT_EVENT_ERROR");
    }
}

void mqtt_init(void) {
    const esp_mqtt_client_config_t mqtt_config={
        .host = mqtt_server,
        .port = 1883
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_start(client);
    esp_mqtt_client_publish(client, "HelloWorld", "HelloFromESP", 0, 0, 0);
    Serial.println("Connected to MQTT_Broker");
}

