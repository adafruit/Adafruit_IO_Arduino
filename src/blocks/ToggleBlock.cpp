/*!
 * @file ToggleBlock.cpp
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
#include "ToggleBlock.h"

/**************************************************************************/
/*!
    @brief  Creates a new Toggle Block on an Adafruit IO Dashboard.
    @param  d
            Adafruit IO Dashboard name.
    @param f
            Adafruit IO Feed to display on the toggle block.
*/
/**************************************************************************/
ToggleBlock::ToggleBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  onText = "1";
  offText = "0";
}

ToggleBlock::~ToggleBlock() {}

/**************************************************************************/
/*!
    @brief  Sets toggle block properties.
    @return String containing properties of the toggle block.
*/
/**************************************************************************/
String ToggleBlock::properties() {
  String props = "{\"onText\":\"";
  props += onText;
  props += "\",\"offText\":\"";
  props += offText;
  props += "\"}";

  return props;
}
