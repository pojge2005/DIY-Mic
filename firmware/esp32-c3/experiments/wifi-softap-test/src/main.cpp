#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char *AP_SSID = "DIY-Mic-Setup";
const char *AP_PASSWORD = "REPLACE_WITH_A_TEST_PASSWORD";

IPAddress localIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);
bool apStarted = false;

void handleRoot()
{
    server.send(200, "text/plain", "DIY-Mic ESP32-C3 WiFi AP is working.");
}

void handleHealth()
{
    String response = "{";
    response += "\"status\":\"online\",";
    response += "\"ip\":\"" + WiFi.softAPIP().toString() + "\",";
    response += "\"clients\":";
    response += String(WiFi.softAPgetStationNum());
    response += "}";
    server.send(200, "application/json", response);
}

void startAccessPoint()
{
    Serial.println("\n[1] Setting WiFi mode...");
    if (!WiFi.mode(WIFI_AP))
    {
        Serial.println("ERROR: WIFI_AP mode failed.");
        return;
    }
    Serial.println("WIFI_AP mode initialized.");

    Serial.println("[2] Configuring AP address...");
    if (!WiFi.softAPConfig(localIP, gateway, subnet))
    {
        Serial.println("ERROR: SoftAP IP configuration failed.");
        return;
    }
    Serial.println("AP address configured.");

    Serial.println("[3] Starting access point...");
    apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD, 6, false, 4);
    if (!apStarted)
    {
        Serial.println("ERROR: SoftAP startup failed.");
        return;
    }

    Serial.println("SUCCESS: Access point started.");
    Serial.printf("SSID: %s\n", AP_SSID);
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, handleRoot);
    server.on("/health", HTTP_GET, handleHealth);
    server.begin();
    Serial.println("HTTP server started.");
}

void setup()
{
    Serial.begin(115200);
    unsigned long start = millis();
    while (!Serial && millis() - start < 10000)
    {
        delay(10);
    }

    delay(500);
    Serial.println("\n================================");
    Serial.println("DIY-Mic WiFi Diagnostic");
    Serial.println("ESP32-C3");
    Serial.println("================================");
    Serial.printf("Chip: %s\n", ESP.getChipModel());
    Serial.printf("CPU: %u MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Free heap: %u bytes\n", ESP.getFreeHeap());
    startAccessPoint();
}

void loop()
{
    static unsigned long lastReport = 0;
    if (apStarted) server.handleClient();

    if (millis() - lastReport >= 3000)
    {
        lastReport = millis();
        Serial.printf(
            "[STATUS] Uptime: %lu s | WiFi mode: %d | AP clients: %u | Heap: %u\n",
            millis() / 1000,
            WiFi.getMode(),
            WiFi.softAPgetStationNum(),
            ESP.getFreeHeap()
        );

        if (apStarted)
        {
            Serial.print("AP IP: ");
            Serial.println(WiFi.softAPIP());
        }
    }

    delay(2);
}
