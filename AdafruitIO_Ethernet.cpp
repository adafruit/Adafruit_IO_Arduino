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
#include "AdafruitIO_Ethernet.h"

AdafruitIO_Ethernet::AdafruitIO_Ethernet(const char *user, const char *key):AdafruitIO(user, key)
{
  _client = new EthernetClient();
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

AdafruitIO_Ethernet::AdafruitIO_Ethernet(const __FlashStringHelper *user, const __FlashStringHelper *key):AdafruitIO(user, key)
{
  _client = new EthernetClient();
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _port);
}

void AdafruitIO_Ethernet::_connect()
{

  if(Ethernet.begin(_mac) == 0)
    _status = AIO_NET_DISCONNECTED;
  else
    _status = AIO_NET_CONNECTED;

}

aio_status_t AdafruitIO_Ethernet::networkStatus()
{
  if(_status == AIO_NET_CONNECTED)
    return _status;

  _connect();
  return _status;
}
