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
    const char* type() { return _visual_type; }

  private:
    const char *_visual_type = "stream";

};

#endif // ADAFRUITIO_STREAMBLOCK_H
