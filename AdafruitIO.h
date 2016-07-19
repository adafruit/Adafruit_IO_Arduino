#ifndef ADAFRUITIO_H
#define ADAFRUITIO_H

#include "Arduino.h"
#include "AdafruitIO_Definitions.h"

class AdafruitIO {

  public:
    AdafruitIO();

    void connect(const char *user, const char *key);
    void connect(const __FlashStringHelper *user, const __FlashStringHelper *key);

    const __FlashStringHelper* statusText();
    virtual aio_status_t status() = 0;
    virtual aio_status_t networkStatus() = 0;
    virtual aio_status_t mqttStatus() = 0;

  protected:
    virtual void _connect() = 0;
    aio_status_t _status = AIO_IDLE;
    const char *_host = "io.adafruit.com";
    uint16_t _port = 8883;
    const char *_username;
    const char *_key;

};

#endif // ADAFRUITIO_H
