#ifndef ADAFRUITIO_H
#define ADAFRUITIO_H

#include "Arduino.h"
#include "Adafruit_MQTT.h"
#include "AdafruitIO_Definitions.h"

class AdafruitIO {

  public:
    AdafruitIO();

    void connect(const char *user, const char *key);
    void connect(const __FlashStringHelper *user, const __FlashStringHelper *key);
    void run();
    void setErrorHandler(AdafruitIOErrorCallbackType cb);

    const __FlashStringHelper* statusText();

    aio_status_t status();
    virtual aio_status_t networkStatus() = 0;
    aio_status_t mqttStatus();

  protected:
    virtual void _connect() = 0;

    aio_status_t _status = AIO_IDLE;
    uint32_t _last_ping = 0;
    Adafruit_MQTT_Subscribe *_subscriptions[MAXSUBSCRIPTIONS];

    Adafruit_MQTT *_mqtt;
    const char *_host = "io.adafruit.com";
    uint16_t _port = 8883;
    const char *_username;
    const char *_key;
    char _err_topic[40];
    char _throttle_topic[42];

  private:
    void _init();

};

#endif // ADAFRUITIO_H
