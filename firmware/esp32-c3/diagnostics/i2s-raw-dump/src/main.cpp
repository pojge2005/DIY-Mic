#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

#define I2S_PORT I2S_NUM_0
#define PIN_I2S_BCLK 4
#define PIN_I2S_WS 5
#define PIN_I2S_SD 3
#define SAMPLE_RATE 16000
#define BUFFER_SAMPLES 256
#define CLIP_THRESHOLD 32760
#define RAW_DUMP_INTERVAL_MS 5000

int32_t rawSamples[BUFFER_SAMPLES];
int32_t minimumSample = INT32_MAX;
int32_t maximumSample = INT32_MIN;
uint32_t peakLevel = 0;
uint32_t clippedSamples = 0;
uint32_t sampleCount = 0;
uint64_t totalSquares = 0;
unsigned long lastReportMs = 0;
unsigned long measurementStartMs = 0;
unsigned long lastRawDumpMs = 0;

bool startMicrophone()
{
    i2s_config_t config = {};
    config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX);
    config.sample_rate = SAMPLE_RATE;
    config.bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT;
    config.channel_format = I2S_CHANNEL_FMT_ONLY_LEFT;
    config.communication_format = I2S_COMM_FORMAT_I2S;
    config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
    config.dma_buf_count = 4;
    config.dma_buf_len = BUFFER_SAMPLES;
    config.use_apll = false;
    config.fixed_mclk = 0;

    esp_err_t result = i2s_driver_install(I2S_PORT, &config, 0, nullptr);
    if (result != ESP_OK)
    {
        Serial.printf("I2S driver error: %d\n", result);
        return false;
    }

    i2s_pin_config_t pins = {};
    pins.bck_io_num = PIN_I2S_BCLK;
    pins.ws_io_num = PIN_I2S_WS;
    pins.data_out_num = I2S_PIN_NO_CHANGE;
    pins.data_in_num = PIN_I2S_SD;

    result = i2s_set_pin(I2S_PORT, &pins);
    if (result != ESP_OK)
    {
        Serial.printf("I2S pin error: %d\n", result);
        i2s_driver_uninstall(I2S_PORT);
        return false;
    }

    i2s_zero_dma_buffer(I2S_PORT);
    return true;
}

void resetMeasurements()
{
    minimumSample = INT32_MAX;
    maximumSample = INT32_MIN;
    peakLevel = 0;
    clippedSamples = 0;
    sampleCount = 0;
    totalSquares = 0;
}

void printRawSamples()
{
    Serial.println("\n--- RAW I2S DATA ---");
    for (size_t i = 0; i < 8; i++)
    {
        Serial.printf("RAW[%u]: 0x%08lX\n",
            (unsigned int)i, (unsigned long)rawSamples[i]);
    }
    Serial.println("--------------------");
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\nDIY-Mic I2S Raw Diagnostic");
    Serial.println("INMP441 - 16 kHz - 32-bit I2S");

    if (!startMicrophone())
    {
        Serial.println("Microphone initialization failed.");
        return;
    }

    Serial.println("I2S initialized.");
    unsigned long now = millis();
    lastReportMs = now;
    measurementStartMs = now;
    lastRawDumpMs = now;
}

void loop()
{
    size_t bytesRead = 0;
    esp_err_t result = i2s_read(
        I2S_PORT, rawSamples, sizeof(rawSamples), &bytesRead, portMAX_DELAY
    );

    if (result != ESP_OK || bytesRead == 0)
    {
        Serial.printf("I2S read error: %d\n", result);
        return;
    }

    size_t count = bytesRead / sizeof(int32_t);
    for (size_t i = 0; i < count; i++)
    {
        int32_t sample24 = rawSamples[i] >> 8;
        int16_t sample16 = (int16_t)(sample24 >> 8);
        int32_t absoluteLevel = abs((int32_t)sample16);

        if (sample16 < minimumSample) minimumSample = sample16;
        if (sample16 > maximumSample) maximumSample = sample16;
        if ((uint32_t)absoluteLevel > peakLevel) peakLevel = absoluteLevel;

        if (sample16 >= CLIP_THRESHOLD || sample16 <= -CLIP_THRESHOLD)
            clippedSamples++;

        totalSquares += (int64_t)sample16 * sample16;
        sampleCount++;
    }

    unsigned long now = millis();
    if (now - lastRawDumpMs >= RAW_DUMP_INTERVAL_MS)
    {
        printRawSamples();
        lastRawDumpMs = now;
    }

    if (now - lastReportMs >= 1000)
    {
        float elapsed = (now - measurementStartMs) / 1000.0f;
        float measuredRate = sampleCount / elapsed;
        float rms = sampleCount > 0
            ? sqrt((double)totalSquares / sampleCount)
            : 0;

        Serial.printf(
            "Rate: %.0f Hz | Min: %ld | Max: %ld | Peak: %lu | RMS: %.1f | Clipped: %lu\n",
            measuredRate, (long)minimumSample, (long)maximumSample,
            (unsigned long)peakLevel, rms, (unsigned long)clippedSamples
        );

        resetMeasurements();
        measurementStartMs = now;
        lastReportMs = now;
    }
}
