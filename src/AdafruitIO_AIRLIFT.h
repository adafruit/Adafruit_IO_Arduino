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
#ifndef ADAFRUITIO_AIRLIFT_H
#define ADAFRUITIO_AIRLIFT_H

#include "Arduino.h"
#include "AdafruitIO.h"
#include "WiFiNINA.h"
#include "SPI.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
  #define BOARDEF 1
  #define SPIWIFI SPI
  #define SPIWIFI_SS _airlift_ss    // Chip select pin
  #define SPIWIFI_ACK _airlift_ack  // a.k.a BUSY or READY pin
  #define ESP32_RESETN _airlift_rst // Reset pin
  #define ESP32_GPIO0 -1 // Not connected
#endif

class AdafruitIO_AIRLIFT : public AdafruitIO {

  public:
    AdafruitIO_AIRLIFT(const char *user, const char *key, const char *ssid, const char *pass):AdafruitIO(user, key)
    {
      _ssid = ssid;
      _pass = pass;
      _mqtt_client = new WiFiSSLClient;
      _mqtt = new Adafruit_MQTT_Client(_mqtt_client, _host, _mqtt_port);
      _http_client = new WiFiSSLClient;
      _http = new HttpClient(*_http_client, _host, _http_port);
    }

    ~AdafruitIO_AIRLIFT()
    {
      if (_mqtt_client)
        delete _http_client;
      if (_http_client)
        delete _mqtt_client;
      if (_mqtt)
        delete _mqtt;
      if (_http)
        delete _http;
    }

    aio_status_t networkStatus()
    {
      switch (WiFi.status())
      {
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

    const char *connectionType()
    {
      return "AIRLIFT";
    }

    //aio_status_t networkStatus();
    //const char* connectionType();

  protected:
    //void _connect();
    const char *_ssid;
    const char *_pass;

    WiFiSSLClient *_http_client;
    WiFiSSLClient *_mqtt_client;

    void _connect()
    {
      // for breakouts, check if the pins would be externally defined
      #ifdef BOARDEF
          WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);
      #endif

      // check esp32 module status
      if (WiFi.status() == WL_NO_MODULE)
      {
        Serial.println("No Module!!");
        Serial.print(WiFi.status());
      }

      WiFi.begin(_ssid, _pass);
      _status = AIO_NET_DISCONNECTED;
  }
};


#endif // ADAFRUITIO_AIRLIFT_H