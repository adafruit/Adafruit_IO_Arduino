/*!
 * @file AdafruitIO_ESP8266.h
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2016 Adafruit Industries
 * Authors: Tony DiCola, Todd Treece
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 */

#ifdef ESP8266

#include "AdafruitIO_ESP8266.h"

AdafruitIO_ESP8266::AdafruitIO_ESP8266(const char *user, const char *key,
                                       const char *ssid, const char *pass)
    : AdafruitIO(user, key) {
  _ssid = ssid;
  _pass = pass;
  // Uncomment the following lines and remove the existing WiFiClient and MQTT
  // client constructors to use Secure MQTT with ESP8266.
  // _client = new WiFiClientSecure;
  // _client->setFingerprint(AIO_SSL_FINGERPRINT);
  // _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _client = new WiFiClient;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, 1883);
  _http = new HttpClient(*_client, _host, _http_port);
}

AdafruitIO_ESP8266::AdafruitIO_ESP8266(const char *user, const char *key)
    : AdafruitIO(user, key) {

 _ssid = NULL;
 _pass = NULL;
  // Uncomment the following lines and remove the existing WiFiClient and MQTT
  // client constructors to use Secure MQTT with ESP8266.
  // _client = new WiFiClientSecure;
  // _client->setFingerprint(AIO_SSL_FINGERPRINT);
  // _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_port);
  _client = new WiFiClient;
  _mqtt = new Adafruit_MQTT_Client(_client, _host, 1883);
  _http = new HttpClient(*_client, _host, _http_port);
}

AdafruitIO_ESP8266::~AdafruitIO_ESP8266() {
  if (_client)
    delete _client;
  if (_mqtt)
    delete _mqtt;
}

void AdafruitIO_ESP8266::_connect() {
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
}
}

/**************************************************************************/
/*!
    @brief    Disconnect the wifi network.
*/
/**************************************************************************/
void AdafruitIO_ESP8266::_disconnect() {
  WiFi.disconnect();
  delay(AIO_NET_DISCONNECT_WAIT);
}

aio_status_t AdafruitIO_ESP8266::networkStatus() {

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

const char *AdafruitIO_ESP8266::connectionType() { return "wifi"; }

#endif // ESP8266
