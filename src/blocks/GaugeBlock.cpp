/*!
 * @file GaugeBlock.cpp
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
#include "GaugeBlock.h"

/**************************************************************************/
/*!
    @brief  Creates a new Gauge Block on an Adafruit IO Dashboard.
    @param  d
            Adafruit IO Dashboard name.
    @param f
            Adafruit IO Feed to display on the Gauge.
*/
/**************************************************************************/
GaugeBlock::GaugeBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  min = 0;
  max = 100;
  ringWidth = "thin";
  label = "Value";
}

GaugeBlock::~GaugeBlock() {}

/**************************************************************************/
/*!
    @brief  Sets Gauge block properties.
    @return String containing properties of the Gauge block.
*/
/**************************************************************************/
String GaugeBlock::properties() {
  int w = 0;

  if (strcmp(ringWidth, "thin")) {
    w = 25;
  } else {
    w = 50;
  }

  String props = "{\"minValue\":\"";
  props += min;
  props += "\",\"maxValue\":\"";
  props += max;
  props += "\",\"ringWidth\":\"";
  props += w;
  props += "\",\"label\":\"";
  props += label;
  props += "\"}";

  return props;
}
