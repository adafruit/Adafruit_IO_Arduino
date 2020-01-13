/*!
 * @file SliderBlock.cpp
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
#include "SliderBlock.h"

SliderBlock::SliderBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  min = 0;
  max = 100;
  step = 10;
  label = "Value";
}

SliderBlock::~SliderBlock() {}

String SliderBlock::properties() {
  String props = "{\"min\":\"";
  props += min;
  props += "\",\"max\":\"";
  props += max;
  props += "\",\"step\":\"";
  props += step;
  props += "\",\"label\":\"";
  props += label;
  props += "\"}";

  return props;
}
