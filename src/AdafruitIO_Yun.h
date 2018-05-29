//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2017, 2018 Imre Horvath
// Authors: Imre Horvath
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_YUN_H
#define ADAFRUITIO_YUN_H

#ifdef ARDUINO_AVR_YUN

#include "Arduino.h"
#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "BridgeSSLClient.h"

class AdafruitIO_Yun : public AdafruitIO {

  public:
    AdafruitIO_Yun(const char *user, const char *key);
    ~AdafruitIO_Yun();

    aio_status_t networkStatus();
    const char* connectionType();

  protected:
    void _connect();

    BridgeSSLClient *_client;

    uint16_t _mqtt_port = 8883;

};

#endif //ARDUINO_AVR_YUN
#endif // ADAFRUITIO_YUN_H
