/*!
 * @file TextBlock.cpp
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
#include "TextBlock.h"

TextBlock::TextBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  fontSize = "small";
}

TextBlock::~TextBlock() {}

String TextBlock::properties() {
  int s = 0;

  if ((strcmp(fontSize, "small") == 0)) {
    s = 12;
  } else if ((strcmp(fontSize, "medium") == 0)) {
    s = 18;
  } else {
    s = 24;
  }

  String props = "{\"fontSize\":\"";
  props += s;
  props += "\"}";

  return props;
}
