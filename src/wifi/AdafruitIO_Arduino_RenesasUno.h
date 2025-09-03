/*!
 * @file AdafruitIO_Arduino_RenesasUno.h
 *
 * This is part of Adafruit IO Arduino. It is designed specifically to work
 * with Arduino Renesas Uno WiFi Rev 4 and Arduino Minima.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Brent Rubell for Adafruit Industries, 2025
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
#ifndef ADAFRUITIO_RENESAS_UNO_H
#define ADAFRUITIO_RENESAS_UNO_H

#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include "SPI.h"
#include "WiFiS3.h"

/****************************************************************************/
/*!
    @brief  Class that stores functions for interacting with Uno R4 Devices
*/
/****************************************************************************/
class AdafruitIO_Arduino_RenesasUno : public AdafruitIO {

public:
  /**************************************************************************/
  /*!
  @brief  Initializes the Adafruit IO class for Uno R4 devices.
  @param    user
            A reference to the Adafruit IO user, shared by AdafruitIO.
  @param    key
            A reference to the Adafruit IO Key, shared by AdafruitIO.
  @param    ssid
            A reference to the WiFi network SSID.
  @param    pass
            A reference to the WiFi network password.
  */
  /**************************************************************************/
  AdafruitIO_Arduino_RenesasUno(const char *user, const char *key,
                                const char *ssid, const char *pass)
      : AdafruitIO(user, key) {
    _ssid = ssid;
    _pass = pass;
    _mqtt_client = new WiFiSSLClient;
    _mqtt = new Adafruit_MQTT_Client(_mqtt_client, _host, _mqtt_port);
    _http_client = new WiFiSSLClient;
    _http = new HttpClient(*_http_client, _host, _http_port);
  }

  /**************************************************************************/
  /*!
  @brief  Destructor for the Adafruit IO AirLift class.
  */
  /**************************************************************************/
  ~AdafruitIO_Arduino_RenesasUno() {
    if (_mqtt_client)
      delete _http_client;
    if (_http_client)
      delete _mqtt_client;
    if (_mqtt)
      delete _mqtt;
    if (_http)
      delete _http;
  }

  /********************************************************/
  /*!
  @brief  Returns the network status of an ESP32 module.
  @return aio_status_t
  */
  /********************************************************/
  aio_status_t networkStatus() {
    switch (WiFi.status()) {
    case WL_CONNECTED:
      return AIO_NET_CONNECTED;
    case WL_CONNECT_FAILED:
      return AIO_NET_CONNECT_FAILED;
    case WL_CONNECTION_LOST:
      return AIO_NET_CONNECT_FAILED;
    case WL_DISCONNECTED:
      return AIO_NET_DISCONNECTED;
    case WL_NO_MODULE:
      return AIO_NET_DISCONNECTED;
    case WL_IDLE_STATUS:
      return AIO_IDLE;
    default:
      return AIO_NET_DISCONNECTED;
    }
  }

  /*****************************************************************/
  /*!
  @brief  Returns the type of network connection used by AdafruitIO.
  @return RENESASUNOR4
  */
  /*****************************************************************/
  const char *connectionType() { return "RENESASUNOR4"; }

protected:
  const char *_ssid;
  const char *_pass;
  WiFiSSLClient *_http_client;
  WiFiSSLClient *_mqtt_client;

  /**************************************************************************/
  /*!
  @brief  Attempts to establish a WiFi connection with the wireless network,
  given _ssid and _pass from the AdafruitIO_Arduino_RenesasUno constructor.
  */
  /**************************************************************************/
  void _connect() {
    if (strlen(_ssid) == 0) {
      _status = AIO_SSID_INVALID;
    } else {

      // check for the WiFi module:
      if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        return;
      }

      String fv = WiFi.firmwareVersion();
      if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.print("Firmware version ");
        Serial.print(fv);
        Serial.print(" is outdated. Latest version is ");
        Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
        Serial.println("Please upgrade the WiFiS3 firmware!");
        return;
      }

      // disconnect from possible previous connection
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
  void _disconnect() {
    WiFi.disconnect();
    delay(AIO_NET_DISCONNECT_WAIT);
  }
};

#endif // ADAFRUITIO_RENESAS_UNO_H
