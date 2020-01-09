/*!
 * @file AdafruitIO_GaugeBlock.h
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
#ifndef ADAFRUITIO_GAUGEBLOCK_H
#define ADAFRUITIO_GAUGEBLOCK_H

#include "AdafruitIO_Block.h"

class GaugeBlock : public AdafruitIO_Block {

public:
  GaugeBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~GaugeBlock();

  int min;
  int max;

  const char *ringWidth;
  const char *label;

  int width = 4;
  int height = 4;

  String properties();
  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "gauge";

  int _width() { return width; }
  int _height() { return height; }
  int _row() { return row; }
  int _column() { return column; }
};

#endif // ADAFRUITIO_GAUGEBLOCK_H
