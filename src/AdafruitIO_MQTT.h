/*!
 * @file AdafruitIO_MQTT.h
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
#ifndef ADAFRUITIO_MQTT_H
#define ADAFRUITIO_MQTT_H

#include "Arduino.h"

/**************************************************************************/
/*!
    @brief  Class that contains MQTT subscription callbacks.
*/
/**************************************************************************/
class AdafruitIO_MQTT {

public:
  AdafruitIO_MQTT() {}
  /**************************************************************************/
  /*!
  @brief    Creates an instance of a MQTT subscription callback.
  @param    val
            Value from the MQTT subscription callback.
  @param    len
            Length of returned value.
  @return   True
  */
  /**************************************************************************/
  virtual void subCallback(char *val, uint16_t len) = 0;
};

#endif // ADAFRUITIO_MQTT_H
