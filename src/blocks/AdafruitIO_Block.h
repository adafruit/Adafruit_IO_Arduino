/*!
 * @file AdafruitIO_Block.h
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
#ifndef ADAFRUITIO_BLOCK_H
#define ADAFRUITIO_BLOCK_H

#include "AdafruitIO_Definitions.h"
#include "Arduino.h"

class AdafruitIO_Dashboard;
class AdafruitIO_Feed;

class AdafruitIO_Block {

public:
  AdafruitIO_Block(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~AdafruitIO_Block();

  int width = 2;
  int height = 2;
  int row = 0;
  int column = 0;

  virtual String properties();
  String dimensions();

  virtual const char *type();

  bool save();

protected:
  AdafruitIO_Dashboard *_dashboard;
  AdafruitIO_Feed *_feed;

  const char *_visual_type;

  virtual int _width() { return width; }
  virtual int _height() { return height; }
  virtual int _row() { return row; }
  virtual int _column() { return column; }
};

#endif // ADAFRUITIO_BLOCK_H
