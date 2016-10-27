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
#ifndef ADAFRUITIO_TOGGLEBLOCK_H
#define ADAFRUITIO_TOGGLEBLOCK_H

#include "AdafruitIO_Block.h"

class ToggleBlock : public AdafruitIO_Block {

  public:
    ToggleBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
    ~ToggleBlock();

    const char *onText;
    const char *offText;

    String properties();
    const char* type() { return _visual_type; }

  private:
    const char *_visual_type;

};

#endif // ADAFRUITIO_TOGGLEBLOCK_H
