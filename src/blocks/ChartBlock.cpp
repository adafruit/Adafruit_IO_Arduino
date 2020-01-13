/*!
 * @file ChartBlock.cpp
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
#include "ChartBlock.h"

ChartBlock::ChartBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f)
    : AdafruitIO_Block(d, f) {
  historyHours = 0;
  xAxisLabel = "X";
  yAxisLabel = "Y";
  yAxisMin = 0;
  yAxisMax = 100;
}

ChartBlock::~ChartBlock() {}

String ChartBlock::properties() {

  String props = "{\"historyHours\":\"";
  props += historyHours;
  props += "\",\"xAxisLabel\":\"";
  props += xAxisLabel;
  props += "\",\"yAxisLabel\":\"";
  props += yAxisLabel;
  props += "\",\"yAxisMin\":\"";
  props += yAxisMin;
  props += "\",\"yAxisMax\":\"";
  props += yAxisMax;
  props += "\"}";

  return props;
}
