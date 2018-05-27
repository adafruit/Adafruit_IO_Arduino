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
#ifdef ARDUINO_AVR_YUN

#include "Arduino.h"
#include "AdafruitIO_Yun.h"
#include "BridgeHttpClient.h"
#include "Process.h"

AdafruitIO_Yun::AdafruitIO_Yun(const char *user, const char *key):AdafruitIO(user, key)
{
  _client = new BridgeClient;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _http = new BridgeHttpClient;
}

AdafruitIO_Yun::~AdafruitIO_Yun()
{
  if(_client)
    delete _client;
  if(_mqtt)
    delete _mqtt;
  if (_http)
    delete _http;
}

void AdafruitIO_Yun::_connect()
{
  // Initialize Bridge and use the on-board LED as a visual indicator
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  AIO_DEBUG_PRINT(F("Bridge version: "));
  AIO_DEBUG_PRINTLN(Bridge.getBridgeVersion());

  _status = AIO_NET_DISCONNECTED;
}

aio_status_t AdafruitIO_Yun::networkStatus()
{
  Process p;
  p.runShellCommand(F("route | grep '^default'"));

  while (p.running());

  if (p.exitValue() == 0) {
    return AIO_NET_CONNECTED;
  }
  return AIO_NET_DISCONNECTED;
}

const char* AdafruitIO_Yun::connectionType()
{
  return "yun";
}

#endif // ARDUINO_AVR_YUN
