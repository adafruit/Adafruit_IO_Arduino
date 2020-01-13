/*!
 * @file AdafruitIO_AIRLIFT.h
 *
 * This is part of Adafruit IO Arduino. It is designed specifically to work
 * with Adafruit's AirLift ESP32 Co-Processor.
 *
 * The ESP32 uses SPI to communicate. Three lines (CS, ACK, RST) are required
 * to communicate with the ESP32.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Brent Rubell for Adafruit Industries.
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
#ifndef ADAFRUITIO_AIRLIFT_H
#define ADAFRUITIO_AIRLIFT_H

#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include "SPI.h"
#include "WiFiNINA.h"

#define NINAFWVER                                                              \
  "1.0.0" /*!< nina-fw version compatible with this library.                   \
           */

/****************************************************************************/
/*!
    @brief  Class that stores functions for interacting with AirLift Devices
*/
/****************************************************************************/
class AdafruitIO_AIRLIFT : public AdafruitIO {

public:
  /**************************************************************************/
  /*!
  @brief  Initializes the Adafruit IO class for AirLift devices.
  @param    user
            A reference to the Adafruit IO user, shared by AdafruitIO.
  @param    key
            A reference to the Adafruit IO Key, shared by AdafruitIO.
  @param    ssid
            A reference to the WiFi network SSID.
  @param    pass
            A reference to the WiFi network password.
  @param    ssPin
            A reference to the ESP32_SS Pin.
  @param    ackPin
            A reference to the ESP32_ACK Pin.
  @param    rstPin
            A reference to the ESP32_RST Pin.
  @param    gpio0Pin
            A reference to the gpio0Pin Pin.
  @param    wifi
            A reference to a SPIClass
  */
  /**************************************************************************/
  AdafruitIO_AIRLIFT(const char *user, const char *key, const char *ssid,
                     const char *pass, int ssPin, int ackPin, int rstPin,
                     int gpio0Pin, SPIClass *wifi)
      : AdafruitIO(user, key) {
    _wifi = wifi;
    _ssPin = ssPin;
    _ackPin = ackPin;
    _rstPin = rstPin;
    _gpio0Pin = gpio0Pin;
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
  ~AdafruitIO_AIRLIFT() {
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
  @brief  Checks the version of an ESP32 module against
  NINAFWVER. Raises an error if the firmware needs to be
  upgraded.
  */
  /********************************************************/
  void firmwareCheck() {
    _fv = WiFi.firmwareVersion();
    if (_fv < NINAFWVER) {
      AIO_DEBUG_PRINTLN("Please upgrade the firmware on the ESP module");
    }
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
    case WL_IDLE_STATUS:
      return AIO_IDLE;
    default:
      return AIO_NET_DISCONNECTED;
    }
  }

  /*****************************************************************/
  /*!
  @brief  Returns the type of network connection used by AdafruitIO.
  @return AIRLIFT
  */
  /*****************************************************************/
  const char *connectionType() { return "AIRLIFT"; }

protected:
  const char *_ssid;
  const char *_pass;
  String _fv = "0.0.0";
  int _ssPin, _ackPin, _rstPin, _gpio0Pin = -1;

  WiFiSSLClient *_http_client;
  WiFiSSLClient *_mqtt_client;

  SPIClass *_wifi;

  /**************************************************************************/
  /*!
  @brief  Attempts to establish a WiFi connection with the wireless network,
  given _ssid and _pass from the AdafruitIO_AIRLIFT constructor.
  */
  /**************************************************************************/
  void _connect() {
    if (strlen(_ssid) == 0) {
      _status = AIO_SSID_INVALID;
    } else {
      _disconnect();
      // setup ESP32 pins
      if (_ssPin != -1) {
        WiFi.setPins(_ssPin, _ackPin, _rstPin, _gpio0Pin, _wifi);
      }

      // check esp32 module version against NINAFWVER
      firmwareCheck();

      // check for esp32 module
      if (WiFi.status() == WL_NO_MODULE) {
        AIO_DEBUG_PRINTLN("No ESP32 module detected!");
        return;
      }

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

#endif // ADAFRUITIO_AIRLIFT_H