#ifndef ADAFRUITIO_H
#define ADAFRUITIO_H

#include "Arduino.h"
#include "Adafruit_MQTT.h"
#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_Feed.h"
#include "AdafruitIO_Data.h"

#ifndef ADAFRUIT_MQTT_VERSION_MAJOR
  #error "This sketch requires Adafruit MQTT Library v0.15.0 or higher. Please install or upgrade using the Library Manager."
#endif

#if ADAFRUIT_MQTT_VERSION_MAJOR == 0 && ADAFRUIT_MQTT_VERSION_MINOR < 15
  #error "This sketch requires Adafruit MQTT Library v0.15.0 or higher. Please install or upgrade using the Library Manager."
#endif

class AdafruitIO {

  friend class AdafruitIO_Feed;

  public:
    AdafruitIO();
    ~AdafruitIO();

    void connect(const char *user, const char *key);
    void connect(const __FlashStringHelper *user, const __FlashStringHelper *key);
    void run();
    void setErrorHandler(SubscribeCallbackBufferType cb);

    AdafruitIO_Feed* feed(const char *name);
    AdafruitIO_Feed* feed(const __FlashStringHelper *name);
    const __FlashStringHelper* statusText();

    aio_status_t status();
    virtual aio_status_t networkStatus() = 0;
    aio_status_t mqttStatus();

  protected:
    virtual void _connect() = 0;

    aio_status_t _status = AIO_IDLE;
    uint32_t _last_ping = 0;

    Adafruit_MQTT *_mqtt;
    const char *_host = IO_HOST;
    uint16_t _port = 8883;
    const char *_username;
    const char *_key;

    char *_err_topic;
    char *_throttle_topic;

    Adafruit_MQTT_Subscribe *_err_sub;
    Adafruit_MQTT_Subscribe *_throttle_sub;

  private:
    void _init();

};

#endif // ADAFRUITIO_H
