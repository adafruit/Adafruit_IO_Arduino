#ifndef ADAFRUITIO_ESP8266_H
#define ADAFRUITIO_ESP8266_H

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
    aio_status_t status();
    aio_status_t networkStatus();
    aio_status_t mqttStatus();

  protected:
    void _connect();
    const char *_ssid;
    const char *_pass;
    WiFiClientSecure *_client;

};

#endif // ADAFRUITIO_ESP8266_H
