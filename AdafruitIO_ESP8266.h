#ifndef ADAFRUITIO_ESP8266_H
#define ADAFRUITIO_ESP8266_H

#ifdef ESP8266

#include "Arduino.h"
#include "AdafruitIO.h"
#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

class AdafruitIO_ESP8266 : public AdafruitIO {

  public:
    AdafruitIO_ESP8266(const char *ssid, const char *pass);
    AdafruitIO_ESP8266(const __FlashStringHelper *ssid, const __FlashStringHelper *pass);
    aio_status_t networkStatus();

  protected:
    void _connect();
    const char *_ssid;
    const char *_pass;
    WiFiClientSecure *_client;

};

#endif //ESP8266
#endif // ADAFRUITIO_ESP8266_H
