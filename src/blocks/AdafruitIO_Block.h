//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_BLOCK_H
#define ADAFRUITIO_BLOCK_H

#include "Arduino.h"
#include "AdafruitIO_Definitions.h"

class AdafruitIO_Dashboard;
class AdafruitIO_Feed;

class AdafruitIO_Block {

  public:
    AdafruitIO_Block(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
    ~AdafruitIO_Block();

    int width = 2;
    int height = 2;
    int row;
    int column;

    virtual String properties();
    virtual const char* type();

    bool save();

  private:
    AdafruitIO_Dashboard *_dashboard;
    AdafruitIO_Feed *_feed;
    const char *_visual_type;

};

#endif // ADAFRUITIO_BLOCK_H
