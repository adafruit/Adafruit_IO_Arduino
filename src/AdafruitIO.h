/*!
 * @file AdafruitIO.h
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

#ifndef ADAFRUITIO_H
#define ADAFRUITIO_H

#include "AdafruitIO_Dashboard.h"
#include "AdafruitIO_Data.h"
#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_Feed.h"
#include "AdafruitIO_Group.h"
#include "AdafruitIO_Time.h"
#include "Adafruit_MQTT.h"
#include "Arduino.h"
#include "ArduinoHttpClient.h"
#include "util/AdafruitIO_Board.h"

#ifndef ADAFRUIT_MQTT_VERSION_MAJOR
#error                                                                         \
    "This sketch requires Adafruit MQTT Library v1.0.0 or higher. Please install or upgrade using the Library Manager."
#endif

#if ADAFRUIT_MQTT_VERSION_MAJOR == 1 && ADAFRUIT_MQTT_VERSION_MINOR < 0
#error                                                                         \
    "This sketch requires Adafruit MQTT Library v1.0.0 or higher. Please install or upgrade using the Library Manager."
#endif

/**************************************************************************/
/*!
    @brief  Class for interacting with Adafruit IO
*/
/**************************************************************************/
class AdafruitIO {
  /**
   * @brief AdafruitIO_Feed addition.
   * @relates AdafruitIO_Feed
   */
  friend class AdafruitIO_Feed;

  /**
   * @brief AdafruitIO_Group addition.
   * @relates AdafruitIO_Group
   */
  friend class AdafruitIO_Group;

  /**
   * @brief AdafruitIO_Dashboard addition.
   * @relates AdafruitIO_Dashboard
   */
  friend class AdafruitIO_Dashboard;

  /**
   * @brief AdafruitIO_Block addition.
   * @relates AdafruitIO_Block
   */
  friend class AdafruitIO_Block;

  /**
   * @brief AdafruitIO_Time addition.
   * @relates AdafruitIO_Time
   */
  friend class AdafruitIO_Time;

public:
  AdafruitIO(const char *user, const char *key);
  virtual ~AdafruitIO();

  void connect();
  void wifi_disconnect();
  aio_status_t run(uint16_t busywait_ms = 0, bool fail_fast = false);

  AdafruitIO_Feed *feed(const char *name);
  AdafruitIO_Feed *feed(const char *name, const char *owner);
  AdafruitIO_Group *group(const char *name);
  AdafruitIO_Dashboard *dashboard(const char *name);
  AdafruitIO_Time *time(aio_time_format_t format);

  const __FlashStringHelper *statusText();

  aio_status_t status();
  /********************************************************************/
  /*!
  @brief   Returns network module status.
  @return  0
  */
  /*******************************************************************/
  virtual aio_status_t networkStatus() = 0;

  /********************************************************************/
  /*!
  @brief  Returns MQTT connection status.
  */
  /*******************************************************************/
  aio_status_t mqttStatus(bool fail_fast = false);

  char *boardID();
  const char *boardType();
  char *version();
  char *userAgent();

  /********************************************************************/
  /*!
  @brief   Returns the Adafruit IO network module connection type.
  @return  0
  */
  /*******************************************************************/
  virtual const char *connectionType() = 0;

protected:
  /********************************************************************/
  /*!
  @brief   Establishes a connection with the Adafruit IO MQTT broker.
  @return  0
  */
  /*******************************************************************/
  virtual void _connect() = 0;

  /******************************************************/
  /*!
  @brief   Disconnects from the Adafruit IO MQTT broker.
  @return  0
  */
  /*****************************************************/
  virtual void _disconnect() = 0;

  aio_status_t _status = AIO_IDLE; /*!< Adafruit IO Connection Status */
  uint32_t _last_ping =
      0; /*!< Previous time when client pinged Adafruit IO, in milliseconds */
  uint32_t _last_mqtt_connect = 0; /*!< Previous time when client connected to
                                      Adafruit IO, in milliseconds */

  Adafruit_MQTT *_mqtt; /*!< Reference to Adafruit_MQTT, _mqtt. */
  HttpClient *_http;    /*!< Reference to HTTPClient, _http */

  char _version[10]; /*!< Adafruit IO Arduino library version */

  const char *_host = "io.adafruit.com"; /*!< Adafruit IO URL */
  uint16_t _mqtt_port = 8883;            /*!< Adafruit IO MQTT SSL port */
  uint16_t _mqtt_eth_port =
      1883; /*!< Adafruit IO MQTT insecure port, used by ethernet clients. */
  uint16_t _http_port = 443; /*!< Adafruit IO HTTP SSL port */

  uint16_t _packetread_timeout; /*!< Maximum amount of time to wait before
                                   processing packets. */

  const char *_username; /*!< Adafruit IO Username. */
  const char *_key;      /*!< Adafruit IO Key. */

  char *_err_topic;      /*!< Adafruit IO MQTT error message topic. */
  char *_throttle_topic; /*!< Adafruit IO MQTT throttle message topic. */
  char *_user_agent;     /*!< Identifies the Adafruit IO client. */

  Adafruit_MQTT_Subscribe
      *_err_sub; /*!< Subscription to Adafruit IO Error topic. */
  Adafruit_MQTT_Subscribe
      *_throttle_sub; /*!< Subscription to Adafruit IO Throttle topic. */

private:
  void _init();
};

#endif // ADAFRUITIO_H
