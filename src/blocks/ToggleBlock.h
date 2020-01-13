/*!
 * @file ToggleBlock.h
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
#ifndef ADAFRUITIO_TOGGLEBLOCK_H
#define ADAFRUITIO_TOGGLEBLOCK_H

#include "AdafruitIO_Block.h"

class ToggleBlock : public AdafruitIO_Block {

public:
  ToggleBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~ToggleBlock();

  const char *onText;
  const char *offText;

  int width = 4;
  int height = 2;

  String properties();
  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "toggle_button";

  int _width() { return width; }
  int _height() { return height; }
  int _row() { return row; }
  int _column() { return column; }
};

#endif // ADAFRUITIO_TOGGLEBLOCK_H
