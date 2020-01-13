/*!
 * @file MomentaryBlock.cpp
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
#include "MomentaryBlock.h"

/**************************************************************************/
/*!
    @brief  Creates a new Momentary Block on an Adafruit IO Dashboard.
    @param  d
            Adafruit IO Dashboard name.
    @param f
            Adafruit IO Feed to display on the momentary.
*/
/**************************************************************************/
MomentaryBlock::MomentaryBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  text = "RESET";
  value = "1";
  release = "0";
}

MomentaryBlock::~MomentaryBlock() {}

/**************************************************************************/
/*!
    @brief  Sets momentary block properties.
    @return String containing properties of the momentary block.
*/
/**************************************************************************/
String MomentaryBlock::properties() {
  String props = "{\"text\":\"";
  props += text;
  props += "\",\"value\":\"";
  props += value;
  props += "\",\"release\":\"";
  props += release;
  props += "\"}";

  return props;
}
