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

#if defined(ARDUINO_SAMD_MKR1000)

  #include "wifi/AdafruitIO_MKR1000.h"
  typedef AdafruitIO_MKR1000 AdafruitIO_WiFi;

#elif defined(USE_AIRLIFT)

  #include "wifi/AdafruitIO_AIRLIFT.h"
  typedef AdafruitIO_AIRLIFT AdafruitIO_WiFi;

#elif defined(USE_WINC1500) 

  #include "wifi/AdafruitIO_WINC1500.h"
  typedef AdafruitIO_WINC1500 AdafruitIO_WiFi;

#elif defined(ARDUINO_ARCH_ESP32)

  #include "wifi/AdafruitIO_ESP32.h"
  typedef AdafruitIO_ESP32 AdafruitIO_WiFi;

#elif defined(ESP8266)

  #include "wifi/AdafruitIO_ESP8266.h"
  typedef AdafruitIO_ESP8266 AdafruitIO_WiFi;

#elif defined(ARDUINO_STM32_FEATHER)

  #include "wifi/AdafruitIO_WICED.h"
  typedef AdafruitIO_WICED AdafruitIO_WiFi;

#else

  #error "Must define USE_AIRLIFT or USE_WINC1500 before including this file."

#endif

#endif // ADAFRUITIO_WIFI_H
