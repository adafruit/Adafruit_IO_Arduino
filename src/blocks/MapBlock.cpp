/*!
 * @file MapBlock.cpp
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
#include "MapBlock.h"

MapBlock::MapBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  historyHours = 0;
  tile = "contrast";
}

MapBlock::~MapBlock() {}

String MapBlock::properties() {

  if ((strcmp(tile, "contrast") != 0) && (strcmp(tile, "street") != 0) &&
      (strcmp(tile, "sat") != 0)) {
    tile = "contrast";
  }

  props = "{\"historyHours\":\"";
  props += historyHours;
  props += "\",\"tile\":\"";
  props += tile;
  props += "\"}";

  return props;
}
