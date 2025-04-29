#include <iostream>
#include "WiFi.h"

#define DEBUG 1

static void in(std::string message) {
    std::cout << "***In function " + message << std::endl;
} 

static void out(std::string message) {
    std::cout << "***Out function " + message << std::endl;
} 

int main () {
    in("main");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    int numNetworks;
    if((numNetworks = WiFi.scanNetworks()) > 0) {
        std::cout << "Found networks" << std::endl;
    } else {
        std::cout << "Didn't find any networks" << std::endl;
    }
    out("main");
    return 0;
}

