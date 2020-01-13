/*!
 * @file ChartBlock.h
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
#ifndef ADAFRUITIO_CHARTBLOCK_H
#define ADAFRUITIO_CHARTBLOCK_H

#include "AdafruitIO_Block.h"

class ChartBlock : public AdafruitIO_Block {

public:
  ChartBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~ChartBlock();

  const char *type() { return _visual_type; }

  int historyHours;
  const char *xAxisLabel;
  const char *yAxisLabel;
  int yAxisMin;
  int yAxisMax;

  int width = 6;
  int height = 4;

  String properties();

protected:
  const char *_visual_type = "line_chart";

  int _width() { return width; }
  int _height() { return height; }
  int _row() { return row; }
  int _column() { return column; }
};

#endif // ADAFRUITIO_CHARTBLOCK_H
