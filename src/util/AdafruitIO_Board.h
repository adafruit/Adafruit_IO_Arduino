//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2017 Adafruit Industries
// Authors: Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
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
  static char _id[64];  /*!< Board Identifier. */
  static char *id();

  static const char _type[];  /*!< Board name. */
  static const char *type();  /*!< Board name. */
};

#endif // ADAFRUITIO_BOARD_H
