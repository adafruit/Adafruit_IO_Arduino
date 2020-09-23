/*!
 * @file AdafruitIO_MKR1010.cpp
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2016 Adafruit Industries
 * Authors: Tony DiCola, Todd Treece, Morgan Winters
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 */

#if defined(ARDUINO_SAMD_MKR1010)

#include "AdafruitIO_MKR1010.h"

AdafruitIO_MKR1010::AdafruitIO_MKR1010(const char *user, const char *key,
                                       const char *ssid, const char *pass)
    : AdafruitIO(user, key) {
  _ssid = ssid;
  _pass = pass;
  _client = new WiFiSSLClient;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _http = new HttpClient(*_client, _host, _http_port);
}

AdafruitIO_MKR1010::~AdafruitIO_MKR1010() {
  if (_client)
    delete _client;
  if (_mqtt)
    delete _mqtt;
}

void AdafruitIO_MKR1010::_connect() {
  if (strlen(_ssid) == 0) {
    _status = AIO_SSID_INVALID;
  } else {
    // no shield? bail
    if (WiFi.status() == WL_NO_SHIELD)
      return;

    _disconnect();

    WiFi.begin(_ssid, _pass);
    _status = AIO_NET_DISCONNECTED;
  }
}

/**************************************************************************/
/*!
    @brief    Disconnect the wifi network.
*/
/**************************************************************************/
void AdafruitIO_MKR1010::_disconnect() {
  WiFi.disconnect();
  delay(AIO_NET_DISCONNECT_WAIT);
}

aio_status_t AdafruitIO_MKR1010::networkStatus() {

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

const char *AdafruitIO_MKR1010::connectionType() { return "wifi"; }

#endif // ARDUINO_ARCH_SAMD
