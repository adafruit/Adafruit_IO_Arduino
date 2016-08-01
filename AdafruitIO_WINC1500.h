#ifndef ADAFRUITIO_WINC1500_H
#define ADAFRUITIO_WINC1500_H

#include "Arduino.h"
#include "AdafruitIO.h"
#include "SPI.h"
#include "Adafruit_WINC1500.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2

class AdafruitIO_WINC1500 : public AdafruitIO {

  public:
    AdafruitIO_WINC1500(const char *ssid, const char *pass);
    AdafruitIO_WINC1500(const __FlashStringHelper *ssid, const __FlashStringHelper *pass);
    aio_status_t networkStatus();

  protected:
    void _connect();
    const char *_ssid;
    const char *_pass;
    Adafruit_WINC1500SSLClient *_client;

};

#endif // ADAFRUITIO_WINC1500_H
