/*!
 * @file StreamBlock.h
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
#ifndef ADAFRUITIO_STREAMBLOCK_H
#define ADAFRUITIO_STREAMBLOCK_H

#include "AdafruitIO_Block.h"

class StreamBlock : public AdafruitIO_Block {

public:
  StreamBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~StreamBlock();

  const char *fontSize;
  const char *fontColor;
  bool showErrors;
  bool showTimestamp;
  bool showName;

  int width = 6;
  int height = 4;

  String properties();
  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "stream";

  int _width() { return width; }
  int _height() { return height; }
  int _row() { return row; }
  int _column() { return column; }
};

#endif // ADAFRUITIO_STREAMBLOCK_H
