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
#ifndef ADAFRUITIO_DASHBOARD_H
#define ADAFRUITIO_DASHBOARD_H

#include "Arduino.h"
#include "AdafruitIO_Definitions.h"
#include "blocks/ToggleBlock.h"
#include "blocks/MomentaryBlock.h"
#include "blocks/SliderBlock.h"
#include "blocks/GaugeBlock.h"

// forward declaration
class AdafruitIO;
class AdafruitIO_Feed;

class AdafruitIO_Dashboard {

  public:
    AdafruitIO_Dashboard(AdafruitIO *io, const char *name);
    ~AdafruitIO_Dashboard();

    const char *name;

    bool exists();
    bool create();

    ToggleBlock* addToggleBlock(AdafruitIO_Feed *feed);
    MomentaryBlock* addMomentaryBlock(AdafruitIO_Feed *feed);
    SliderBlock* addSliderBlock(AdafruitIO_Feed *feed);
    GaugeBlock* addGaugeBlock(AdafruitIO_Feed *feed);

  private:
    AdafruitIO *_io;

};

#endif // ADAFRUITIO_DASHBOARD_H
