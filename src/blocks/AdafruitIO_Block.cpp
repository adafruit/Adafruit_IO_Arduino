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
#include "AdafruitIO_Block.h"

AdafruitIO_Block::AdafruitIO_Block(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
{
  _dashboard = d;
  _feed = f;
}

AdafruitIO_Block::~AdafruitIO_Block(){}

String AdafruitIO_Block::properties()
{
  String props = "";
  return props;
}

bool AdafruitIO_Block::save()
{
  Serial.println(properties());
}
