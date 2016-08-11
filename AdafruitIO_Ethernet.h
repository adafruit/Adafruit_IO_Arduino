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
#ifndef ADAFRUITIO_Ethernet_H
#define ADAFRUITIO_Ethernet_H


#include "Arduino.h"
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#if __has_include("Ethernet2.h")
  #include <Ethernet2.h>
#else
  #include <Ethernet.h>
#endif

#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>

#include "AdafruitIO.h"

class AdafruitIO_Ethernet : public AdafruitIO {

  public:
    AdafruitIO_Ethernet(const char *user, const char *key);
    AdafruitIO_Ethernet(const __FlashStringHelper *user, const __FlashStringHelper *key);

    aio_status_t networkStatus();

  protected:
    void _connect();

    byte _mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    uint16_t _port = 1883;

    EthernetClient *_client;

};

#endif // ADAFRUITIO_Ethernet_H
