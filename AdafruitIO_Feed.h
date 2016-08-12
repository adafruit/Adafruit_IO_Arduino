//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
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
    ~AdafruitIO_Feed();

    void onMessage(AdafruitIODataCallbackType cb);

    bool save(char *value, double lat=0, double lon=0, double ele=0);
    bool save(bool value, double lat=0, double lon=0, double ele=0);
    bool save(String value, double lat=0, double lon=0, double ele=0);
    bool save(int value, double lat=0, double lon=0, double ele=0);
    bool save(unsigned int value, double lat=0, double lon=0, double ele=0);
    bool save(long value, double lat=0, double lon=0, double ele=0);
    bool save(unsigned long value, double lat=0, double lon=0, double ele=0);
    bool save(float value, double lat=0, double lon=0, double ele=0, int precision=6);
    bool save(double value, double lat=0, double lon=0, double ele=0, int precision=6);

    void setLocation(double lat, double lon, double ele=0);

    void subCallback(char *val, uint16_t len);
    const char *name;

    AdafruitIO_Data *data;

  private:
    void _init();

    char *_topic;

    Adafruit_MQTT_Subscribe *_sub;
    Adafruit_MQTT_Publish *_pub;

    AdafruitIO *_io;
    AdafruitIO_Data *_data;
    AdafruitIODataCallbackType _dataCallback;

};

#endif // ADAFRUITIO_FEED_H
