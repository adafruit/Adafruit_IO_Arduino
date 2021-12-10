/*!
 * @file AdafruitIO_MKR1010.h
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2016 Adafruit Industries
 * Authors: David Goldstein, Morgan Winters
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 */

#ifndef ADAFRUITIO_MKR1010_H
#define ADAFRUITIO_MKR1010_H

#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include "SPI.h"
#include "WiFiNINA.h"
#include "WiFiSSLClient.h"

class AdafruitIO_MKR1010 : public AdafruitIO {

public:
  AdafruitIO_MKR1010(const char *user, const char *key, const char *ssid,
                     const char *pass)
      : AdafruitIO(user, key) {
    _ssid = ssid;
    _pass = pass;
    _client = new WiFiSSLClient;
    _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
    _http = new HttpClient(*_client, _host, _http_port);
  }
  ~AdafruitIO_MKR1010() {
    if (_client)
      delete _client;
    if (_mqtt)
      delete _mqtt;
  }

  aio_status_t networkStatus() {
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

  const char *connectionType() { return "wifi"; }

protected:
  void _connect() {
    if (strlen(_ssid) == 0) {
      _status = AIO_SSID_INVALID;
    } else {
      _disconnect();

      WiFi.begin(_ssid, _pass);
      _status = networkStatus();
    }
  }

  void _disconnect() {
    WiFi.disconnect();
    delay(AIO_NET_DISCONNECT_WAIT);
  }

  const char *_ssid;
  const char *_pass;

  WiFiSSLClient *_client;
};

#endif ADAFRUITIO_MKR1010_H
