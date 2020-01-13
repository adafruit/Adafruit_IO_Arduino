/*!
 * @file AdafruitIO_Definitions.h
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

#ifndef ADAFRUITIO_DEFINITIONS_H_
#define ADAFRUITIO_DEFINITIONS_H_

#define ADAFRUITIO_VERSION_MAJOR 3 ///< Adafruit IO Arduino Major Semvar
#define ADAFRUITIO_VERSION_MINOR 2 ///< Adafruit IO Arduino Minor Semvar
#define ADAFRUITIO_VERSION_PATCH 0 ///< Adafruit IO Arduino Patch Semvar

// forward declaration
class AdafruitIO_Data;

typedef void (*AdafruitIODataCallbackType)(
    AdafruitIO_Data *data); /*!< Data callback type */

/**************************************************************************/
/*!
    @brief  Class that contains methods for Adafruit IO MQTT callbacks.
*/
/**************************************************************************/
class AdafruitIOGroupCallback {
public:
  /**************************************************************************/
  /*!
      @brief  Sets up MQTT Group callbacks.
      @param  f
              Valid Adafruit IO feed key.
      @param  cb
              Adafruit IO MQTT callback.
  */
  /**************************************************************************/
  AdafruitIOGroupCallback(const char *f, AdafruitIODataCallbackType cb) {
    feed = f;
    dataCallback = cb;
    next_cb = 0;
  }

  /**************************************************************************/
  /*!
      @brief  Sets up MQTT Group callbacks.
      @param  cb
              Adafruit IO MQTT callback.
  */
  /**************************************************************************/
  AdafruitIOGroupCallback(AdafruitIODataCallbackType cb) {
    feed = 0;
    dataCallback = cb;
    next_cb = 0;
  }

  const char *feed; /*!< Adafruit IO feed name. */
  AdafruitIODataCallbackType
      dataCallback; /*!< data carried by an AdafruitIOGroupCallback. */
  AdafruitIOGroupCallback *next_cb; /*!< Next callback number. */
};

// Uncomment/comment to turn on/off debug output messages.
// #define AIO_DEBUG
// Uncomment/comment to turn on/off error output
// #define AIO_ERROR

// note: if you're using something like Zero or Due, change the below to
// SerialUSB
#define AIO_PRINTER Serial ///< Where debug messages will be printed

// Define actual debug output functions when necessary.
#ifdef AIO_DEBUG
#define AIO_DEBUG_PRINT(...)                                                   \
  { AIO_PRINTER.print(__VA_ARGS__); } ///< Prints debug output.
#define AIO_DEBUG_PRINTLN(...)                                                 \
  { AIO_PRINTER.println(__VA_ARGS__); } ///< Prints line from debug output.
#else
#define AIO_DEBUG_PRINT(...)                                                   \
  {} ///< Prints debug output
#define AIO_DEBUG_PRINTLN(...)                                                 \
  {} ///< Prints line from debug output.
#endif

// Define actual error output functions when necessary.
#ifdef AIO_ERROR
#define AIO_ERROR_PRINT(...)                                                   \
  { AIO_PRINTER.print(__VA_ARGS__); } ///< Prints error output
#define AIO_ERROR_PRINTLN(...)                                                 \
  { AIO_PRINTER.println(__VA_ARGS__); } ///< Prints line from error output
#else
#define AIO_ERROR_PRINT(...)                                                   \
  {} ///< Prints error output.
#define AIO_ERROR_PRINTLN(...)                                                 \
  {} ///< Prints line from error output.
#endif

#define AIO_PING_INTERVAL 60000 ///< Adafruit IO Ping Interval, in milliseconds
#define AIO_THROTTLE_RECONNECT_INTERVAL                                        \
  60000 ///< Time to wait between re-connecting to Adafruit IO after throttled
#define AIO_MQTT_CONNECTION_TIMEOUT                                            \
  60000 ///< Time to wait for a successful reconnection after MQTT disconnect
#define AIO_NET_CONNECTION_TIMEOUT                                             \
  60000 ///< Time to wait for a successful reconnection after network disconnect
#define AIO_NET_DISCONNECT_WAIT                                                \
  300 ///< Time to wait for a net disconnect to take effect

#define AIO_ERROR_TOPIC "/errors"      ///< Adafruit IO Error MQTT Topic
#define AIO_THROTTLE_TOPIC "/throttle" ///< Adafruit IO Throttle MQTT Topic

// latest fingerprint can be generated with
// echo | openssl s_client -connect io.adafruit.com:443 | openssl x509
// -fingerprint -noout
#define AIO_SSL_FINGERPRINT                                                    \
  "77 00 54 2D DA E7 D8 03 27 31 23 99 EB 27 DB CB A5 4C 57 18" ///< Latest
                                                                ///< Adafruit IO
                                                                ///< SSL
                                                                ///< Fingerprint

#define AIO_FEED_NAME_LENGTH 20 ///< Maximum length of an Adafruit IO Feed name
#define AIO_DATA_LENGTH                                                        \
  45 ///< Maximum length of data sent/recieved from Adafruit IO
#define AIO_CSV_LENGTH                                                         \
  150 ///< Maximum comma-separated-value length from Adafruit IO

/** aio_status_t offers 13 status states */
typedef enum {

  AIO_IDLE = 0,               // Waiting for connection establishement
  AIO_NET_DISCONNECTED = 1,   // Network disconnected
  AIO_DISCONNECTED = 2,       // Disconnected from Adafruit IO
  AIO_FINGERPRINT_UNKOWN = 3, // Unknown AIO_SSL_FINGERPRINT

  AIO_NET_CONNECT_FAILED = 10,  // Failed to connect to network
  AIO_CONNECT_FAILED = 11,      // Failed to connect to Adafruit IO
  AIO_FINGERPRINT_INVALID = 12, // Unknown AIO_SSL_FINGERPRINT
  AIO_AUTH_FAILED = 13, // Invalid Adafruit IO login credentials provided.
  AIO_SSID_INVALID =
      14, // SSID is "" or otherwise invalid, connection not attempted

  AIO_NET_CONNECTED = 20,           // Connected to Adafruit IO
  AIO_CONNECTED = 21,               // Connected to network
  AIO_CONNECTED_INSECURE = 22,      // Insecurely (non-SSL) connected to network
  AIO_FINGERPRINT_UNSUPPORTED = 23, // Unsupported AIO_SSL_FINGERPRINT
  AIO_FINGERPRINT_VALID = 24        // Valid AIO_SSL_FINGERPRINT

} aio_status_t;

/** Three different types of MQTT time feeds from IO */
typedef enum {

  AIO_TIME_SECONDS = 0, // Seconds MQTT feed
  AIO_TIME_MILLIS = 1,  // Milisecond MQTT feed
  AIO_TIME_ISO = 2      // ISO8601 MQTT Feed

} aio_time_format_t;

#endif /* ADAFRUITIO_DEFINITIONS_H_ */
