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
#include "AdafruitIO_Dashboard.h"
#include "AdafruitIO.h"

AdafruitIO_Dashboard::AdafruitIO_Dashboard(AdafruitIO *io, const char *k)
{
  _io = io;
  key = k;
}

AdafruitIO_Dashboard::~AdafruitIO_Dashboard(){}
