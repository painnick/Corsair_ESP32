#include <Arduino.h>

#include "esp_log.h"

#include "Mp3Controller.h"

#define MAIN_TAG "Main"

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_RX 16 // dfplayer(FIXED)
#define PIN_TX 17 // dfplayer(FIXED)
#define PIN_MOTOR 23
#define PIN_GATLING 15

#define PWM_FREQUENCY 1000
#define PWM_RESOLUTION 8
#define CHANNEL_MOTOR 15


bool isMotorOn = true;

void setup() {
#ifdef DEBUG
    ESP_LOGI(MAIN_TAG, "Setup...");
#endif
    pinMode(PIN_GATLING, OUTPUT);

    ledcSetup(CHANNEL_MOTOR, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(PIN_MOTOR, CHANNEL_MOTOR);
    ledcWrite(CHANNEL_MOTOR, 127);

    setupSound();
}

void loop() {
    dfmp3.playMp3FolderTrack(2);

    for(int i = 0; i < 10; i ++) {
        digitalWrite(PIN_GATLING, HIGH);
        delay(100);
        digitalWrite(PIN_GATLING, LOW);
        delay(100);
    }

    dfmp3.stop();

    delay(5000);
}