/*!
 * @file AdafruitIO_Time.h
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
#ifndef ADAFRUITIO_TIME_H
#define ADAFRUITIO_TIME_H

#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_MQTT.h"
#include "Adafruit_MQTT.h"
#include "Arduino.h"

// forward declaration
class AdafruitIO;

typedef void (*AdafruitIOTimeCallbackType)(
    char *value,
    uint16_t len); /*!< an instance of Adafruit IO's time callback. */

/**************************************************************************/
/*!
    @brief  Class that contains functions for interacting with
            the Adafruit IO Time Service.
*/
/**************************************************************************/
class AdafruitIO_Time : public AdafruitIO_MQTT {

public:
  AdafruitIO_Time(AdafruitIO *io, aio_time_format_t f);
  ~AdafruitIO_Time();
  void onMessage(AdafruitIOTimeCallbackType cb);
  void subCallback(char *val, uint16_t len);
  char *data;               /*!< Data sent by Adafruit IO's time service. */
  aio_time_format_t format; /*!< Adafruit IO time format,
                               TIME_SECONDS/TIME_MILLIS/TIME_ISO. */

private:
  AdafruitIOTimeCallbackType _dataCallback;
  void _init();
  char *_topic;
  Adafruit_MQTT_Subscribe *_sub;
  AdafruitIO *_io;
};

#endif // ADAFRUITIO_FEED_H
