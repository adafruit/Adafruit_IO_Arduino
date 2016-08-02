#ifndef ADAFRUITIO_WICED_H
#define ADAFRUITIO_WICED_H

#ifdef ARDUINO_STM32_FEATHER

#include "Arduino.h"
#include "AdafruitIO.h"
#include <adafruit_feather.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

class AdafruitIO_WICED : public AdafruitIO {

  public:
    AdafruitIO_WICED(const char *ssid, const char *pass);
    AdafruitIO_WICED(const __FlashStringHelper *ssid, const __FlashStringHelper *pass);
    aio_status_t networkStatus();

  protected:
    void _connect();
    const char *_ssid;
    const char *_pass;
    uint16_t _port = 1883;
    AdafruitTCP *_client;

};

#endif // ARDUINO_STM32_FEATHER

#endif // ADAFRUITIO_WICED_H