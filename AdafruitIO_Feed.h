#ifndef ADAFRUITIO_FEED_H
#define ADAFRUITIO_FEED_H

#include "Arduino.h"
#include "Adafruit_MQTT.h"

// forward declaration
class AdafruitIO;

class AdafruitIO_Feed {

  public:
    AdafruitIO_Feed(AdafruitIO *io, const char *name);
    AdafruitIO_Feed(AdafruitIO *io, const __FlashStringHelper *name);
    void onMessage(SubscribeCallbackBufferType cb);
    void onMessage(SubscribeCallbackDoubleType cb);
    void onMessage(SubscribeCallbackUInt32Type cb);

    bool save(const char *s);
    bool save(double f, uint8_t precision=2);
    bool save(int32_t i);
    bool save(uint32_t i);
    bool save(uint8_t *b, uint16_t bLen);

  private:
    void _init();
    const char *_name;
    AdafruitIO *_io;
    char *_topic;
    Adafruit_MQTT_Subscribe *_sub;
    Adafruit_MQTT_Publish *_pub;

};

#endif // ADAFRUITIO_FEED_H
