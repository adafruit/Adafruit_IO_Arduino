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
#ifndef ADAFRUITIO_H
#define ADAFRUITIO_H

#include "Arduino.h"
#include "Adafruit_MQTT.h"
#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_Feed.h"
#include "AdafruitIO_Group.h"
#include "AdafruitIO_Dashboard.h"
#include "AdafruitIO_Data.h"
#include "ArduinoHttpClient.h"
#include "util/AdafruitIO_Board.h"

#ifndef ADAFRUIT_MQTT_VERSION_MAJOR
  #error "This sketch requires Adafruit MQTT Library v0.17.0 or higher. Please install or upgrade using the Library Manager."
#endif

#if ADAFRUIT_MQTT_VERSION_MAJOR == 0 && ADAFRUIT_MQTT_VERSION_MINOR < 17
  #error "This sketch requires Adafruit MQTT Library v0.17.0 or higher. Please install or upgrade using the Library Manager."
#endif

// Uncomment/comment to turn on/off debug output messages.
// #define IO_DEBUG
// Uncomment/comment to turn on/off error output messages.
#define IO_ERROR

// Set where debug messages will be printed.
#define IO_DEBUG_PRINTER Serial
// If using something like Zero or Due, change the above to SerialUSB

// Define actual debug output functions when necessary.
#ifdef IO_DEBUG
  #define IO_DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define IO_DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
  #define IO_DEBUG_PRINTBUFFER(buffer, len) { printBuffer(buffer, len); }
#else
  #define IO_DEBUG_PRINT(...) {}
  #define IO_DEBUG_PRINTLN(...) {}
  #define IO_DEBUG_PRINTBUFFER(buffer, len) {}
#endif

#ifdef IO_ERROR
  #define IO_ERROR_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define IO_ERROR_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
  #define IO_ERROR_PRINTBUFFER(buffer, len) { printBuffer(buffer, len); }
#else
  #define IO_ERROR_PRINT(...) {}
  #define IO_ERROR_PRINTLN(...) {}
  #define IO_ERROR_PRINTBUFFER(buffer, len) {}
#endif


class AdafruitIO {

  friend class AdafruitIO_Feed;
  friend class AdafruitIO_Group;
  friend class AdafruitIO_Dashboard;
  friend class AdafruitIO_Block;

  public:
    AdafruitIO(const char *user, const char *key);
    virtual ~AdafruitIO();

    void connect();

    void run(uint16_t busywait_ms = 0);

    AdafruitIO_Feed* feed(const char *name);
    AdafruitIO_Group* group(const char *name);
    AdafruitIO_Dashboard* dashboard(const char *name);

    const __FlashStringHelper* statusText();

    aio_status_t status();
    virtual aio_status_t networkStatus() = 0;
    aio_status_t mqttStatus();

    char* boardID();
    const char* boardType();
    char* version();
    char* userAgent();
    virtual const char* connectionType() = 0;

  protected:
    virtual void _connect() = 0;
    aio_status_t _status = AIO_IDLE;
    uint32_t _last_ping = 0;

    Adafruit_MQTT *_mqtt;
    HttpClient *_http;

    char _version[10];

    const char *_host = "io.adafruit.com";
    uint16_t _mqtt_port = 8883;
    uint16_t _http_port = 443;

    uint16_t _packetread_timeout;

    const char *_username;
    const char *_key;

    char *_err_topic;
    char *_throttle_topic;
    char *_user_agent;

    Adafruit_MQTT_Subscribe *_err_sub;
    Adafruit_MQTT_Subscribe *_throttle_sub;

  private:
    void _init();

};

#endif // ADAFRUITIO_H
