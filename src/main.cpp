#include <Arduino.h>

#include "esp_log.h"

#include "Mp3Controller.h"

#define MAIN_TAG "Main"

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_RX 16 // dfplayer(FIXED)
#define PIN_TX 17 // dfplayer(FIXED)
#define PIN_GATLING_LIGHT 15
#define PIN_GATLING_BUTTON 36

void setup() {
#ifdef DEBUG
    ESP_LOGI(MAIN_TAG, "Setup...");
#endif
    pinMode(PIN_GATLING_LIGHT, OUTPUT);

    setupSound();

    dfmp3.playMp3FolderTrack(1);
    dfmp3.loop();
    dfmp3.setRepeatPlayCurrentTrack(true);
    dfmp3.loop();
}

void loop() {
    uint16_t val = analogRead(PIN_GATLING_BUTTON);
    if (val < 255) {
#ifdef DEBUG
        ESP_LOGI(MAIN_TAG, "Click!");
#endif
        dfmp3.playAdvertisement(1);
        dfmp3.loop();

        for (int i = 0; i < 5; i++) {
            digitalWrite(PIN_GATLING_LIGHT, HIGH);
            delay(100);
            digitalWrite(PIN_GATLING_LIGHT, LOW);
            delay(100);
        }
        dfmp3.stopAdvertisement();
        dfmp3.loop();

#ifdef DEBUG
        static int count = 0;
        auto isExplosion = (++count) % 3 == 1;
#else
        auto isExplosion = random(0, 10) == 1;
#endif
        if (isExplosion) {
#ifdef DEBUG
            ESP_LOGI(MAIN_TAG, "Explosion!!!");
#endif
            delay(1000);
            dfmp3.playAdvertisement(2);
            dfmp3.loop();
            delay(1400);
            dfmp3.stopAdvertisement();
            dfmp3.loop();
        }
    }
}