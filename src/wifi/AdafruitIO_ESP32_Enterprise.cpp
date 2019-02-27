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
#ifdef ARDUINO_ARCH_ESP32

#include "AdafruitIO_ESP32_Enterprise.h"

AdafruitIO_ESP32_Enterprise::AdafruitIO_ESP32_Enterprise(const char *user, const char *key, const char *ssid, const char *identity, const char *pass, const char *ca_pem) : AdafruitIO_ESP32(user, key, ssid, pass)
{
    _identity = identity;
    _ca_pem = ca_pem;
}

AdafruitIO_ESP32_Enterprise::~AdafruitIO_ESP32_Enterprise()
{
}

void AdafruitIO_ESP32_Enterprise::_connect()
{

  delay(100);
  WiFi.mode(WIFI_STA); // set to station mode

  if(_ca_pem != NULL) {
    esp_wifi_sta_wpa2_ent_set_ca_cert((uint8_t *)_ca_pem, strlen(_ca_pem)); // provide CA certificate, this is necessary for security
  }

  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)_identity, strlen(_identity)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)_identity, strlen(_identity)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)_pass, strlen(_pass)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default for WPA2
  esp_wifi_sta_wpa2_ent_enable(&config); // pass WPA2 config to the stack
  WiFi.begin(_ssid);
  delay(100);
  _status = AIO_NET_DISCONNECTED;

}

#endif // ARDUINO_ARCH_ESP32
