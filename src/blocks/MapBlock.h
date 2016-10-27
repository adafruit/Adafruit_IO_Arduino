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
#ifndef ADAFRUITIO_MAPBLOCK_H
#define ADAFRUITIO_MAPBLOCK_H

#include "AdafruitIO_Block.h"

class MapBlock : public AdafruitIO_Block {

  public:
    MapBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
    ~MapBlock();

    int historyHours;
    const char *tile;

    String properties();
    const char* type() { return _visual_type; }

  private:
    const char *_visual_type;

};

#endif // ADAFRUITIO_MAPBLOCK_H
