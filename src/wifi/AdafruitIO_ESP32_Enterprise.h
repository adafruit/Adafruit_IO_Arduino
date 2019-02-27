//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2019 Adafruit Industries
// Authors: Tony DiCola, Todd Treece, David Ryskalczyk
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_ESP32_ENTERPRISE_H
#define ADAFRUITIO_ESP32_ENTERPRISE_H

#ifdef ARDUINO_ARCH_ESP32

#include "Arduino.h"
#include "AdafruitIO.h"
#include <WiFi.h>
#include "esp_wpa2.h"
#include "WiFiClientSecure.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "wifi/AdafruitIO_ESP32.h"

class AdafruitIO_ESP32_Enterprise : public AdafruitIO_ESP32 {

  public:
    AdafruitIO_ESP32_Enterprise(const char *user, const char *key, const char *ssid, const char *identity, const char *pass, const char *ca_pem);
    ~AdafruitIO_ESP32_Enterprise();

  protected:

    void _connect();

    const char *_identity;
    const char *_ca_pem;

};

#endif //ESP32
#endif // ADAFRUITIO_ESP32_ENTERPRISE_H
