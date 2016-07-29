#ifndef ADAFRUITIO_FEED_H
#define ADAFRUITIO_FEED_H

#include "Arduino.h"
#include "Adafruit_MQTT.h"
#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_Data.h"

// forward declaration
class AdafruitIO;

class AdafruitIO_Feed {

  public:
    AdafruitIO_Feed(AdafruitIO *io, const char *name);
    AdafruitIO_Feed(AdafruitIO *io, const __FlashStringHelper *name);

    void onMessage(AdafruitIODataCallbackType cb);

    bool save(const char *s);
    bool save(double f, uint8_t precision=2);
    bool save(int32_t i);
    bool save(uint32_t i);
    bool save(uint8_t *b, uint16_t bLen);

    void subCallback(char *val, uint16_t len);
    const char *name;

  private:
    void _init();

    char *_sub_topic;
    char *_pub_topic;

    Adafruit_MQTT_Subscribe *_sub;
    Adafruit_MQTT_Publish *_pub;

    AdafruitIO *_io;
    AdafruitIO_Data *_data;
    AdafruitIODataCallbackType _dataCallback;

};

#endif // ADAFRUITIO_FEED_H
