/*!
 * @file AdafruitIO_ImageBlock.h
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
#ifndef ADAFRUITIO_IMAGEBLOCK_H
#define ADAFRUITIO_IMAGEBLOCK_H

#include "AdafruitIO_Block.h"

class ImageBlock : public AdafruitIO_Block {

public:
  ImageBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
      : AdafruitIO_Block(d, f) {}
  ~ImageBlock() {}

  int height = 6;
  int width = 4;

  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "image";

  int _width() { return width; }
  int _height() { return height; }
  int _row() { return row; }
  int _column() { return column; }
};

#endif // ADAFRUITIO_IMAGEBLOCK_H
