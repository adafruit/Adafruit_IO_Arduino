/*!
 * @file StreamBlock.cpp
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
#include "StreamBlock.h"

/**************************************************************************/
/*!
    @brief  Creates a new Stream Block on an Adafruit IO Dashboard.
    @param  d
            Adafruit IO Dashboard name.
    @param f
            Adafruit IO Feed to display on the stream block.
*/
/**************************************************************************/
StreamBlock::StreamBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  fontSize = "small";
  fontColor = "green";
  showErrors = true;
  showTimestamp = true;
  showName = true;
}

StreamBlock::~StreamBlock() {}

/**************************************************************************/
/*!
    @brief  Sets stream block properties.
    @return String containing properties of the stream block.
*/
/**************************************************************************/
String StreamBlock::properties() {
  int s = 0;

  if (strcmp(fontSize, "small") == 0) {
    s = 12;
  }
  if (strcmp(fontSize, "medium") == 0) {
    s = 18;
  } else {
    s = 24;
  }

  String props = "{\"fontSize\":\"";
  props += s;
  props += "\",\"fontColor\":\"";
  props += (strcmp(fontColor, "white") == 0) ? "#ffffff" : "#63de00";
  props += "\",\"errors\":\"";
  props += showErrors ? "yes" : "no";
  props += "\",\"showTimestamp\":\"";
  props += showTimestamp ? "yes" : "no";
  props += "\",\"showName\":\"";
  props += showName ? "yes" : "no";
  props += "\"}";

  return props;
}
