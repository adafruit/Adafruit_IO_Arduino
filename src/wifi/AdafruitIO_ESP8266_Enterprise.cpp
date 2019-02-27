//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2019 Adafruit Industries
// Authors: Tony DiCola, Todd Treece, David Ryskalczyk
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifdef ESP8266

#include "AdafruitIO_ESP8266_Enterprise.h"

AdafruitIO_ESP8266_Enterprise::AdafruitIO_ESP8266_Enterprise(const char *user, const char *key, const char *ssid, const char *identity, const char *pass, const char *ca_pem) : AdafruitIO_ESP8266(user, key, ssid, pass)
{
  _identity = identity;
  _ca_pem = ca_pem;
}

AdafruitIO_ESP8266_Enterprise::~AdafruitIO_ESP8266_Enterprise()
{
}

void AdafruitIO_ESP8266_Enterprise::_connect()
{

  delay(100);
  WiFi.mode(WIFI_STA);

  if (_ca_pem != NULL) {
    wifi_station_set_enterprise_ca_cert((uint8_t *)_ca_pem, strlen(_ca_pem));
  }
  wifi_station_set_wpa2_enterprise_auth(1); // enable WPA2 authentication mode

  wifi_station_set_enterprise_identity((uint8_t *)_identity, strlen(_identity)); //provide identity
  wifi_station_set_enterprise_username((uint8_t *)_identity, strlen(_identity)); //provide username --> identity and username is same
  wifi_station_set_enterprise_password((uint8_t *)_pass, strlen(_pass)); //provide password

  WiFi.begin(_ssid);

  delay(100);
  _status = AIO_NET_DISCONNECTED;

}

#endif // ESP8266
