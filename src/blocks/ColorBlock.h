/*!
 * @file ColorBlock.h
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
#ifndef ADAFRUITIO_COLORBLOCK_H
#define ADAFRUITIO_COLORBLOCK_H

#include "AdafruitIO_Block.h"

class ColorBlock : public AdafruitIO_Block {

public:
  ColorBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
      : AdafruitIO_Block(d, f) {}
  ~ColorBlock() {}

  int width = 4;
  int height = 4;

  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "color_picker";

  int _width() { return width; }
  int _height() { return height; }
  int _row() { return row; }
  int _column() { return column; }
};

#endif // ADAFRUITIO_COLORBLOCK_H
