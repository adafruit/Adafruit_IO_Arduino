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

#include "AdafruitIO_AIRLIFT.h"


AdafruitIO_AIRLIFT::AdafruitIO_AIRLIFT(const char *user, const char *key, const char *ssid, const char *pass):AdafruitIO(user, key)
{
  _ssid = ssid;
  _pass = pass;
  _mqtt_client = new WiFiSSLClient;
  _mqtt = new Adafruit_MQTT_Client(_mqtt_client, _host, _mqtt_port);
  _http_client = new WiFiSSLClient;
  _http = new HttpClient(*_http_client, _host, _http_port);
}

AdafruitIO_AIRLIFT::~AdafruitIO_AIRLIFT()
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


void AdafruitIO_AIRLIFT::_connect()
{
  // for breakouts, check if the pins would be externally defined
  #ifdef BOARDEF
    WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);
  #endif

  // check esp32 module status
  if(WiFi.status() == WL_NO_MODULE){
    Serial.print(WiFi.status());
  }

  WiFi.begin(_ssid, _pass);
  _status = AIO_NET_DISCONNECTED;

}

aio_status_t AdafruitIO_AIRLIFT::networkStatus()
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

const char* AdafruitIO_AIRLIFT::connectionType()
{
  return "AIRLIFT";
}

#endif // ARDUINO_ARCH_SAMD