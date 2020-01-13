/*!
 * @file AdafruitIO_Board.h
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
#ifndef ADAFRUITIO_BOARD_H
#define ADAFRUITIO_BOARD_H

#include "Arduino.h"

#if defined(ARDUINO_ARCH_AVR)
#include <avr/boot.h>
#endif

/**************************************************************************/
/*!
    @brief  Class for dynamically assigning an identifier for the
            development board used with this library.
*/
/**************************************************************************/
class AdafruitIO_Board {

public:
  static char _id[64]; /*!< Board Identifier. */
  static char *id();

  static const char _type[]; /*!< Board name. */
  static const char *type(); /*!< Board name. */
};

#endif // ADAFRUITIO_BOARD_H
