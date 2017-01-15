//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2017 Imre Horvath
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
#include "BridgeClient.h"

class AdafruitIO_Yun : public AdafruitIO {

  public:
    AdafruitIO_Yun(const char *user, const char *key);
    AdafruitIO_Yun(const __FlashStringHelper *user, const __FlashStringHelper *key);
    ~AdafruitIO_Yun();

    aio_status_t networkStatus();
    const char* connectionType();

  protected:
    void _connect();

    // At the time writing this, the latest Yun firmware (OPENWRT-YÚN 1.5.3),
    // comes with Bridge version 101 included, which does not support SSL yet.
    // Therefore we use the insecure- BridgeClient, and MQTT port this time.

    // TODO: Once a new Yun firmware with Bridge 161 or later gets released,
    //       change the library to BridgeSSLClient and MQTT port 8883!

    BridgeClient *_client;  // insecure MQTT client

    uint16_t _mqtt_port = 1883; // insecure MQTT port

};

#endif //ARDUINO_AVR_YUN
#endif // ADAFRUITIO_YUN_H
