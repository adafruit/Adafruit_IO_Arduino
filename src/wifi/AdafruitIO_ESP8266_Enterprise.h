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
#ifndef ADAFRUITIO_ESP8266_ENTERPRISE_H
#define ADAFRUITIO_ESP8266_ENTERPRISE_H

#ifdef ESP8266

#include "Arduino.h"
#include "AdafruitIO.h"
#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "wifi/AdafruitIO_ESP8266.h"
#include "wpa2_enterprise.h"

class AdafruitIO_ESP8266_Enterprise : public AdafruitIO_ESP8266 {

  public:
    AdafruitIO_ESP8266_Enterprise(const char *user, const char *key, const char *ssid, const char *identity, const char *pass, const char *ca_pem);
    ~AdafruitIO_ESP8266_Enterprise();

  protected:
    void _connect();

    const char *_identity;
    const char *_ca_pem;

};

#endif //ESP8266
#endif // ADAFRUITIO_ESP8266_ENTERPRISE_H
