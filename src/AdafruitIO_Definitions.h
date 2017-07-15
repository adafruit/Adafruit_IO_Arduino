//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_DEFINITIONS_H_
#define ADAFRUITIO_DEFINITIONS_H_

#define ADAFRUITIO_VERSION_MAJOR 2
#define ADAFRUITIO_VERSION_MINOR 6
#define ADAFRUITIO_VERSION_PATCH 0

// forward declaration
class AdafruitIO_Data;

typedef void (*AdafruitIODataCallbackType)(AdafruitIO_Data *data);

class AdafruitIOGroupCallback {
  public:
    AdafruitIOGroupCallback(const char *f, AdafruitIODataCallbackType cb) {
      feed = f;
      dataCallback = cb;
      next_cb = 0;
    }

    AdafruitIOGroupCallback(AdafruitIODataCallbackType cb) {
      feed = 0;
      dataCallback = cb;
      next_cb = 0;
    }

    const char *feed;
    AdafruitIODataCallbackType dataCallback;
    AdafruitIOGroupCallback *next_cb;

};

// uncomment/comment to turn on/off error output
#define AIO_ERROR

// where debug messages will be printed
#define AIO_PRINTER Serial

#ifdef AIO_ERROR
  #define AIO_ERR_PRINT(...) { AIO_PRINTER.print(__VA_ARGS__); }
  #define AIO_ERR_PRINTLN(...) { AIO_PRINTER.println(__VA_ARGS__); }
#else
  #define AIO_ERR_PRINT(...) {}
  #define AIO_ERR_PRINTLN(...) {}
#endif

#define AIO_PING_INTERVAL 60000
#define AIO_THROTTLE_RECONNECT_INTERVAL 60000

#define AIO_ERROR_TOPIC "/errors"
#define AIO_THROTTLE_TOPIC "/throttle"

// latest fingerprint can be generated with
// echo | openssl s_client -connect io.adafruit.com:443 |& openssl x509 -fingerprint -noout
#define AIO_SSL_FINGERPRINT "AD 4B 64 B3 67 40 B5 FC 0E 51 9B BD 25 E9 7F 88 B6 2A A3 5B"

#define AIO_FEED_NAME_LENGTH 20
#define AIO_DATA_LENGTH 45
#define AIO_CSV_LENGTH 150

typedef enum {

    // CONNECTING
    AIO_IDLE                    = 0,
    AIO_NET_DISCONNECTED        = 1,
    AIO_DISCONNECTED            = 2,
    AIO_FINGERPRINT_UNKOWN      = 3,

    // FAILURE
    AIO_NET_CONNECT_FAILED      = 10,
    AIO_CONNECT_FAILED          = 11,
    AIO_FINGERPRINT_INVALID     = 12,
    AIO_AUTH_FAILED             = 13,

    // SUCCESS
    AIO_NET_CONNECTED           = 20,
    AIO_CONNECTED               = 21,
    AIO_CONNECTED_INSECURE      = 22,
    AIO_FINGERPRINT_UNSUPPORTED = 23,
    AIO_FINGERPRINT_VALID       = 24

} aio_status_t;

#endif /* ADAFRUITIO_DEFINITIONS_H_ */
