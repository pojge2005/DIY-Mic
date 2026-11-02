#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println();
    Serial.println("DIY-Mic ESP8266 serial bring-up test");
}

void loop() {
    delay(2000);
    Serial.println("Board and serial monitor are running.");
}
