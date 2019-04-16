//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2019 Adafruit Industries
// Authors: Brent Rubell
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#if !defined(ARDUINO_SAMD_MKR1000) && defined(ARDUINO_ARCH_SAMD)

#include "AdafruitIO_AirLift.h"

AdafruitIO_AirLift::AdafruitIO_AirLift(const char *user, const char *key, const char *ssid, const char *pass):AdafruitIO(user, key)
{
  _ssid = ssid;
  _pass = pass;
  _mqtt_client = new WiFiSSLClient;
  _mqtt = new Adafruit_MQTT_Client(_mqtt_client, _host, _mqtt_port);
  _http_client = new WiFiSSLClient;
  _http = new HttpClient(*_http_client, _host, _http_port);
}

AdafruitIO_AirLift::~AdafruitIO_AirLift()
{
  if(_mqtt_client)
    delete _http_client;
  if(_http_client)
    delete _mqtt_client;
  if(_mqtt)
    delete _mqtt;
  if(_http)
    delete _http;
}

void AdafruitIO_AirLift::_connect()
{

  WiFi.setPins(WINC_CS, WINC_IRQ, WINC_RST, WINC_EN);

  // Return if no module detected
  if(WiFi.status() == WL_NO_MODULE)
    return;

  int status = WL_IDLE_STATUS;

  while (status != WL_CONNECTED) {
    WiFi.begin(_ssid, _pass);
    delay(10000);
  }
}

aio_status_t AdafruitIO_AirLift::networkStatus()
{

  switch(WiFi.status()) {
    case WL_CONNECTED:
      return AIO_NET_CONNECTED;
    case WL_CONNECT_FAILED:
      return AIO_NET_CONNECT_FAILED;
    case WL_IDLE_STATUS:
      return AIO_IDLE;
    default:
      return AIO_NET_DISCONNECTED;
  }
}

const char* AdafruitIO_AirLift::connectionType()
{
  return "AirLift";
}

#endif // ARDUINO_ARCH_SAMD
