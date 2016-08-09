//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_FONA_H
#define ADAFRUITIO_FONA_H

#ifdef ARDUINO_ARCH_AVR

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_FONA.h"
#include "AdafruitIO.h"
#include "Adafruit_MQTT_FONA.h"

#define FONA_RX  9
#define FONA_TX  8
#define FONA_RST 4
#define FONA_RI  7
#define FONA_BAUD 4800

class AdafruitIO_FONA : public AdafruitIO {

  public:
    AdafruitIO_FONA(const char *apn, const char *apn_user, const char *apn_pass);
    AdafruitIO_FONA(const __FlashStringHelper *apn, const __FlashStringHelper *apn_user, const __FlashStringHelper *apn_pass);
    aio_status_t networkStatus();

  protected:
    void _connect();

    const char *_apn;
    const char *_apn_user;
    const char *_apn_pass;

    uint16_t _port = 1883;

    SoftwareSerial *_serial;
    Adafruit_FONA *_fona;

};

#endif // ARDUINO_ARCH_AVR

#endif // ADAFRUITIO_FONA_H
