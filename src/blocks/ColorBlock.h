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
#ifndef ADAFRUITIO_COLORBLOCK_H
#define ADAFRUITIO_COLORBLOCK_H

#include "AdafruitIO_Block.h"

class ColorBlock : public AdafruitIO_Block {

  public:
    ColorBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f) : AdafruitIO_Block(d, f) {}
    ~ColorBlock() {}

  private:
    const char *_visual_type = "color_picker";

};

#endif // ADAFRUITIO_COLORBLOCK_H
