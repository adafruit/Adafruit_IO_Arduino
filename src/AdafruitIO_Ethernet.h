/*!
 * @file AdafruitIO_Ethernet.h
 *
 * This is part of the Adafruit IO library for the Arduino platform.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Tony DiCola, Todd Treece for Adafruit Industries
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#ifndef ADAFRUITIO_ETHERNET_H
#define ADAFRUITIO_ETHERNET_H

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include <SPI.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>

#include "AdafruitIO.h"

/**************************************************************************/
/*!
    @brief  Class for interfacing with the Adafruit Ethernet FeatherWing
*/
/**************************************************************************/
class AdafruitIO_Ethernet : public AdafruitIO {

public:
  /**************************************************************************/
  /*!
      @brief    Instanciates an Adafruit Ethernet FeatherWing.
      @param    *user
                Reference to a valid Adafruit IO Username.
      @param    *key
                Reference to a valid Adafruit IO Key.
  */
  /**************************************************************************/
  AdafruitIO_Ethernet(const char *user, const char *key)
      : AdafruitIO(user, key) {
    _client = new EthernetClient();
    _mqtt = new Adafruit_MQTT_Client(_client, _host, _mqtt_eth_port, _username,
                                     _key);
    _http = new HttpClient(*_client, _host, _http_port);
  }

  /**************************************************************************/
  /*!
      @brief    Checks the connection status between the Ethernet
                FeatherWing and Adafruit IO
      @return   True if connected to Adafruit IO, otherwise False.
  */
  /**************************************************************************/
  aio_status_t networkStatus() {
    if (_status == AIO_NET_CONNECTED)
      return _status;

    _connect();
    return _status;
  }

  /**************************************************************************/
  /*!
      @brief    Defines network module type.
      @return   String "ethernet_wing"
  */
  /**************************************************************************/
  const char *connectionType() { return "ethernet_wing"; }

protected:
  byte _mac[6] = {0xDE, 0xAD, 0xBE,
                  0xEF, 0xFE, 0xED}; /*!< Ethernet FeatherWing MAC Address */

  EthernetClient *_client; /*!< Reference to EthernetClient, _client */

  /**************************************************************************/
  /*!
      @brief    Attempts to connect Ethernet FeatherWing to Adafruit IO
  */
  /**************************************************************************/
  void _connect() {
    if (Ethernet.begin(_mac) == 0) {
      _status = AIO_NET_DISCONNECTED;
      if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        AIO_DEBUG_PRINTLN("Ethernet FeatherWing not found! Please recheck "
                          "wiring connections.");
        while (true)
          delay(1); // do nothing, no point running without Ethernet hardware
      }
    } else {
      _status = AIO_NET_CONNECTED;
    }
  }
};

#endif // ADAFRUITIO_ETHERNET_H
