#include <Arduino.h>

unsigned long lastReport = 0;

void setup()
{
    Serial.begin(115200);

    unsigned long start = millis();
    while (!Serial && millis() - start < 5000)
    {
        delay(10);
    }

    Serial.println();
    Serial.println("================================");
    Serial.println("DIY-Mic ESP32-C3 SERIAL TEST");
    Serial.println("================================");

    Serial.printf("Chip: %s\n", ESP.getChipModel());
    Serial.printf("Revision: %d\n", ESP.getChipRevision());
    Serial.printf("CPU: %u MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash: %u bytes\n", ESP.getFlashChipSize());
    Serial.println("Serial initialization successful.");
}

void loop()
{
    if (millis() - lastReport >= 1000)
    {
        lastReport = millis();
        Serial.printf(
            "HEARTBEAT | Uptime: %lu s | Free heap: %u bytes\n",
            millis() / 1000,
            ESP.getFreeHeap()
        );
    }

    delay(10);
}
