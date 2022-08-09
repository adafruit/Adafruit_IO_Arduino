/*!
 * @file AdafruitIO_ESP8266.h
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2016 Adafruit Industries
 * Authors: Tony DiCola, Todd Treece
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 */

#ifndef ADAFRUITIO_ESP8266_H
#define ADAFRUITIO_ESP8266_H

#ifdef ESP8266

#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include "ESP8266WiFi.h"
/* NOTE - Projects that require "Secure MQTT" (TLS/SSL) also require a new
 * SSL certificate every year. If adding Secure MQTT to your ESP8266 project is
 * important  - please switch to using the modern ESP32 (and related models)
 * instead of the ESP8266 to avoid updating the SSL fingerprint every year.
 *
 * If you've read through this and still want to use "Secure MQTT" with your
 * ESP8266 project, we've left the "WiFiClientSecure" lines commented out. To
 * use them, uncomment the commented out lines within `AdafruitIO_ESP8266.h` and
 * `AdafruitIO_ESP8266.cpp` and recompile the library.
 */
// #include "WiFiClientSecure.h"

class AdafruitIO_ESP8266 : public AdafruitIO {

public:
  AdafruitIO_ESP8266(const char *user, const char *key, const char *ssid,
                     const char *pass);
  ~AdafruitIO_ESP8266();

  aio_status_t networkStatus();
  const char *connectionType();

protected:
  void _connect();
  void _disconnect();

  const char *_ssid;
  const char *_pass;
  WiFiClient *_client;
  // Uncomment the following line, and remove the line above, to use
  // secure MQTT with ESP8266.
  // WiFiClientSecure *_client;
};

#endif // ESP8266
#endif // ADAFRUITIO_ESP8266_H
