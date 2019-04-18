//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2019 Adafruit Industries
// Authors: Brent Rubell
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_AIRLIFT_H
#define ADAFRUITIO_AIRLIFT_H

#if !defined(ARDUINO_SAMD_MKR1000) && defined(ARDUINO_ARCH_SAMD)

#include "Arduino.h"
#include "AdafruitIO.h"
#include "WiFiNINA.h"
#include "SPI.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
  #define BOARDEF 1
  #define SPIWIFI SPI
  #define SPIWIFI_SS _airlift_ss    // Chip select pin
  #define SPIWIFI_ACK _airlift_ack  // a.k.a BUSY or READY pin
  #define ESP32_RESETN _airlift_rst // Reset pin
  #define ESP32_GPIO0 -1 // Not connected
#endif

class AdafruitIO_AIRLIFT : public AdafruitIO {

  public:
    AdafruitIO_AIRLIFT(const char *user, const char *key, const char *ssid, const char *pass);
    ~AdafruitIO_AIRLIFT();

    aio_status_t networkStatus();
    const char* connectionType();

  protected:
    void _connect();
    const char *_ssid;
    const char *_pass;

    WiFiSSLClient *_http_client;
    WiFiSSLClient *_mqtt_client;

};

#endif // ARDUINO_ARCH_SAMD

#endif // ADAFRUITIO_AIRLIFT_H