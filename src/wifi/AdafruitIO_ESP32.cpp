/*!
 * @file AdafruitIO_ESP32.cpp
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2021 Adafruit Industries
 * Authors: Tony DiCola, Todd Treece, Brent Rubell
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 */
#ifdef ARDUINO_ARCH_ESP32

#include "AdafruitIO_ESP32.h"

AdafruitIO_ESP32::AdafruitIO_ESP32(const char *user, const char *key,
                                   const char *ssid, const char *pass)
    : AdafruitIO(user, key) {
  _ssid = ssid;
  _pass = pass;
  _client = new WiFiClientSecure;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _http = new HttpClient(*_client, _host, _http_port);
}

AdafruitIO_ESP32::AdafruitIO_ESP32(const char *user, const char *key)
    : AdafruitIO(user, key) {

  _ssid = NULL;
  _pass = NULL;
  _client = new WiFiClientSecure;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _http = new HttpClient(*_client, _host, _http_port);
}


AdafruitIO_ESP32::~AdafruitIO_ESP32() {
  if (_client)
    delete _client;
  if (_mqtt)
    delete _mqtt;
}

void AdafruitIO_ESP32::_connect() {
if (_ssid != NULL) {
  if (strlen(_ssid) == 0) {
    _status = AIO_SSID_INVALID;
  } else {
    _disconnect();
    delay(100);
    WiFi.begin(_ssid, _pass);
    delay(100);
    _status = AIO_NET_DISCONNECTED;
  }
  _client->setCACert(_aio_root_ca);
 }
}

/**************************************************************************/
/*!
    @brief    Disconnect the wifi network.
*/
/**************************************************************************/
void AdafruitIO_ESP32::_disconnect() {
  WiFi.disconnect();
  delay(AIO_NET_DISCONNECT_WAIT);
}

aio_status_t AdafruitIO_ESP32::networkStatus() {
  switch (WiFi.status()) {
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

const char *AdafruitIO_ESP32::connectionType() { return "wifi"; }

#endif // ESP32
