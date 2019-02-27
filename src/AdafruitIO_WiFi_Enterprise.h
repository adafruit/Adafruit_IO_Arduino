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
#ifndef ADAFRUITIO_WIFI_ENTERPRISE_H
#define ADAFRUITIO_WIFI_ENTERPRISE_H

#if defined(ARDUINO_ARCH_ESP32)

  #include "wifi/AdafruitIO_ESP32_Enterprise.h"
  typedef AdafruitIO_ESP32_Enterprise AdafruitIO_WiFi_Enterprise;

#elif defined(ESP8266)

  #include "wifi/AdafruitIO_ESP8266_Enterprise.h"
  typedef AdafruitIO_ESP8266_Enterprise AdafruitIO_WiFi_Enterprise;

#endif

#endif // ADAFRUITIO_WIFI_ENTERPRISE_H
