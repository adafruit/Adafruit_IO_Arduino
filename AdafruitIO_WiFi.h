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
#ifndef ADAFRUITIO_WIFI_H
#define ADAFRUITIO_WIFI_H

#if defined(ARDUINO_ARCH_SAMD) && defined(WINC1501_RESET_PIN)

#include "AdafruitIO_MKR1000.h"

class AdafruitIO_WiFi: public AdafruitIO_MKR1000 {

  public:
    AdafruitIO_WiFi(const char *user, const char *key, const char *ssid, const char *pass) :
      AdafruitIO_MKR1000(user, key, ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *user, const __FlashStringHelper *key, const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_MKR1000(user, key, ssid, pass) {}

};

#elif defined(ARDUINO_ARCH_SAMD) && !defined(WINC1501_RESET_PIN)

#include "AdafruitIO_WINC1500.h"

class AdafruitIO_WiFi: public AdafruitIO_WINC1500 {

  public:
    AdafruitIO_WiFi(const char *user, const char *key, const char *ssid, const char *pass) :
      AdafruitIO_WINC1500(user, key, ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *user, const __FlashStringHelper *key, const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_WINC1500(user, key, ssid, pass) {}

};

#elif defined(ESP8266)

#include "AdafruitIO_ESP8266.h"

class AdafruitIO_WiFi: public AdafruitIO_ESP8266 {

  public:
    AdafruitIO_WiFi(const char *user, const char *key, const char *ssid, const char *pass) :
      AdafruitIO_ESP8266(user, key, ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *user, const __FlashStringHelper *key, const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_ESP8266(user, key, ssid, pass) {}

};

#elif defined(ARDUINO_STM32_FEATHER)

#include "AdafruitIO_WICED.h"

class AdafruitIO_WiFi: public AdafruitIO_WICED {

  public:
    AdafruitIO_WiFi(const char *user, const char *key, const char *ssid, const char *pass) :
      AdafruitIO_WICED(user, key, ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *user, const __FlashStringHelper *key, const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_WICED(user, key, ssid, pass) {}

};

#endif

#endif // ADAFRUITIO_WIFI_H
