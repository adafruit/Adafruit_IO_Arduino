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
#ifndef ADAFRUITIO_ETHERNET_H
#define ADAFRUITIO_ETHERNET_H

#include "Arduino.h"
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>

#include "AdafruitIO.h"

// all logic in .h to avoid auto compile
class AdafruitIO_Ethernet : public AdafruitIO
{

public:
  AdafruitIO_Ethernet(const char *user, const char *key) : AdafruitIO(user, key)
  {
    _client = new EthernetClient();
    _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_eth_port, _username, _key);
    _http = new HttpClient(*_client, _host, _http_port);
  }

  aio_status_t networkStatus()
  {
    if (_status == AIO_NET_CONNECTED)
      return _status;

    _connect();
    return _status;
  }

  const char *connectionType()
  {
    return "ethernet_wing";
  }

protected:
  byte _mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

  EthernetClient *_client;

  void _connect()
  {
    if (Ethernet.begin(_mac) == 0)
    {
      _status = AIO_NET_DISCONNECTED;
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
        AIO_DEBUG_PRINTLN("Ethernet FeatherWing not found! Please recheck wiring connections.");
        while (true)
          delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    else
    {
      _status = AIO_NET_CONNECTED;
    }
  }
};

#endif // ADAFRUITIO_ETHERNET_H
