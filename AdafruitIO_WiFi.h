#ifndef ADAFRUITIO_WIFI_H
#define ADAFRUITIO_WIFI_H

#ifdef ARDUINO_ARCH_SAMD

#include "AdafruitIO_WINC1500.h"

class AdafruitIO_WiFi: public AdafruitIO_WINC1500 {

  public:
    AdafruitIO_WiFi(const char *ssid, const char *pass) :
      AdafruitIO_WINC1500(ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_WINC1500(ssid, pass) {}

};

#elif ESP8266

#include "AdafruitIO_ESP8266.h"

class AdafruitIO_WiFi: public AdafruitIO_ESP8266 {

  public:
    AdafruitIO_WiFi(const char *ssid, const char *pass) :
      AdafruitIO_ESP8266(ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_ESP8266(ssid, pass) {}

};

#elif ARDUINO_STM32_FEATHER

#include "AdafruitIO_WICED.h"

class AdafruitIO_WiFi: public AdafruitIO_WICED {

  public:
    AdafruitIO_WiFi(const char *ssid, const char *pass) :
      AdafruitIO_WICED(ssid, pass) {}
    AdafruitIO_WiFi(const __FlashStringHelper *ssid, const __FlashStringHelper *pass) :
      AdafruitIO_WICED(ssid, pass) {}

};

#endif

#endif // ADAFRUITIO_WIFI_H
