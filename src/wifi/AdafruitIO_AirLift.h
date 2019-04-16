//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef AdafruitIO_AirLift_H
#define AdafruitIO_AirLift_H

#if !defined(ARDUINO_SAMD_MKR1000) && defined(ARDUINO_ARCH_SAMD)

#include "Arduino.h"
#include "AdafruitIO.h"
#include "SPI.h"
#include "WiFiNINA.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
  // Don't change the names of these #define's! they match the variant ones
  #define SPIWIFI SPI
  #define SPIWIFI_SS 10  // Chip select pin
  #define SPIWIFI_ACK 7  // a.k.a BUSY or READY pin
  #define ESP32_RESETN 5 // Reset pin
  #define ESP32_GPIO0 -1 // Not connected
#endif

class AdafruitIO_AirLift : public AdafruitIO {

  public:
    AdafruitIO_AirLift(const char *user, const char *key, const char *ssid, const char *pass);
    ~AdafruitIO_AirLift();

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

#endif // AdafruitIO_AirLift_H
