/*!
 * @file AdafruitIO_RP2040.h
 *
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright 2024 Brent Rubell for Adafruit Industries.
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
#ifndef ADAFRUITIO_RP2040_H
#define ADAFRUITIO_RP2040_H

#ifdef ARDUINO_ARCH_RP2040

#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include <WiFiClientSecure.h>

/****************************************************************************/
/*!
    @brief  Class that stores functions for interacting with the RP2040
            WiFi Client
*/
/****************************************************************************/
class AdafruitIO_RP2040 : public AdafruitIO {

public:
  /**************************************************************************/
  /*!
  @brief  Initializes the Adafruit IO class for RP2040 boards.
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
  AdafruitIO_RP2040(const char *user, const char *key, const char *ssid,
                    const char *pass)
      : AdafruitIO(user, key) {
    _ssid = ssid;
    _pass = pass;
    _mqtt_client = new WiFiClientSecure;
    _mqtt = new Adafruit_MQTT_Client(_mqtt_client, _host, _mqtt_port);
    _http_client = new WiFiClientSecure;
    _http = new HttpClient(*_http_client, _host, _http_port);
  }

  /*******************************/
  /*!
  @brief  Class dtor
  */
  /*******************************/
  ~AdafruitIO_RP2040() {
    if (_mqtt_client)
      delete _http_client;
    if (_http_client)
      delete _mqtt_client;
  }

  /********************************************************/
  /*!
  @brief  Returns the network status of the RP2040.
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

  /******************************************************************/
  /*!
  @brief  Returns the type of network connection used by AdafruitIO.
  @return RP2040
  */
  /******************************************************************/
  const char *connectionType() { return "RP2040"; }

protected:
  const char *_ssid; ///< WiFi network SSID
  const char *_pass; ///< WiFi network password

  WiFiClientSecure *_http_client; ///< HTTP client
  WiFiClientSecure *_mqtt_client; ///< MQTT client

  const char *_aio_root_ca_prod =
      "-----BEGIN CERTIFICATE-----\n"
      "MIIEjTCCA3WgAwIBAgIQDQd4KhM/xvmlcpbhMf/ReTANBgkqhkiG9w0BAQsFADBh\n"
      "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
      "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\n"
      "MjAeFw0xNzExMDIxMjIzMzdaFw0yNzExMDIxMjIzMzdaMGAxCzAJBgNVBAYTAlVT\n"
      "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
      "b20xHzAdBgNVBAMTFkdlb1RydXN0IFRMUyBSU0EgQ0EgRzEwggEiMA0GCSqGSIb3\n"
      "DQEBAQUAA4IBDwAwggEKAoIBAQC+F+jsvikKy/65LWEx/TMkCDIuWegh1Ngwvm4Q\n"
      "yISgP7oU5d79eoySG3vOhC3w/3jEMuipoH1fBtp7m0tTpsYbAhch4XA7rfuD6whU\n"
      "gajeErLVxoiWMPkC/DnUvbgi74BJmdBiuGHQSd7LwsuXpTEGG9fYXcbTVN5SATYq\n"
      "DfbexbYxTMwVJWoVb6lrBEgM3gBBqiiAiy800xu1Nq07JdCIQkBsNpFtZbIZhsDS\n"
      "fzlGWP4wEmBQ3O67c+ZXkFr2DcrXBEtHam80Gp2SNhou2U5U7UesDL/xgLK6/0d7\n"
      "6TnEVMSUVJkZ8VeZr+IUIlvoLrtjLbqugb0T3OYXW+CQU0kBAgMBAAGjggFAMIIB\n"
      "PDAdBgNVHQ4EFgQUlE/UXYvkpOKmgP792PkA76O+AlcwHwYDVR0jBBgwFoAUTiJU\n"
      "IBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsG\n"
      "AQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMDQGCCsGAQUFBwEB\n"
      "BCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQuY29tMEIGA1Ud\n"
      "HwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEds\n"
      "b2JhbFJvb3RHMi5jcmwwPQYDVR0gBDYwNDAyBgRVHSAAMCowKAYIKwYBBQUHAgEW\n"
      "HGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwDQYJKoZIhvcNAQELBQADggEB\n"
      "AIIcBDqC6cWpyGUSXAjjAcYwsK4iiGF7KweG97i1RJz1kwZhRoo6orU1JtBYnjzB\n"
      "c4+/sXmnHJk3mlPyL1xuIAt9sMeC7+vreRIF5wFBC0MCN5sbHwhNN1JzKbifNeP5\n"
      "ozpZdQFmkCo+neBiKR6HqIA+LMTMCMMuv2khGGuPHmtDze4GmEGZtYLyF8EQpa5Y\n"
      "jPuV6k2Cr/N3XxFpT3hRpt/3usU/Zb9wfKPtWpoznZ4/44c1p9rzFcZYrWkj3A+7\n"
      "TNBJE0GmP2fhXhP1D/XVfIW/h0yCJGEiV9Glm/uGOa3DXHlmbAcxSyCRraG+ZBkA\n"
      "7h4SeM6Y8l/7MBRpPCz6l8Y=\n"
      "-----END CERTIFICATE-----\n"; ///< Root certificate for io.adafruit.com

  /**************************************************************************/
  /*!
  @brief  Attempts to establish a WiFi connection with the wireless network,
  given _ssid and _pass from the AdafruitIO_RP2040 constructor.
  */
  /**************************************************************************/
  void _connect() {
    if (strlen(_ssid) == 0) {
      Serial.println("Invalid SSID!");
      _status = AIO_SSID_INVALID;
    } else {
      _disconnect();
      delay(10000);
      WiFi.mode(WIFI_STA);
      WiFi.setTimeout(20000);
      WiFi.begin(_ssid, _pass);
      Serial.println("\nConnecting");
      _status = AIO_NET_DISCONNECTED;
    }
    _mqtt_client->setCACert(_aio_root_ca_prod);
  }

  /**************************************************************************/
  /*!
      @brief    Disconnects from the wifi network.
  */
  /**************************************************************************/
  void _disconnect() {
    WiFi.disconnect();
    delay(AIO_NET_DISCONNECT_WAIT);
  }
};

#endif // ADAFRUITIO_RP2040_H
#endif // ARDUINO_ARCH_RP2040
