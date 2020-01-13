/*!
 * @file GaugeBlock.h
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
#ifndef ADAFRUITIO_GAUGEBLOCK_H
#define ADAFRUITIO_GAUGEBLOCK_H

#include "AdafruitIO_Block.h"

/**************************************************************************/
/*!
    @brief  Class for interacting with the Adafruit IO Dashboard
            Gauge Block.
*/
/**************************************************************************/
class GaugeBlock : public AdafruitIO_Block {

public:
  GaugeBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~GaugeBlock();

  int min; /*!< Min. value displayed on gauge. */
  int max; /*!< Max. value displayed on gauge. */

  const char *ringWidth; /*!< Width of gauge's ring. */
  const char *label;     /*!< Gauge text label. */

  int width = 4;  /*!< Dashboard block width. */
  int height = 4; /*!< Dashboard block height. */

  String properties();

  /******************************************/
  /*!
      @brief  Returns block type
      @return Block type.
  */
  /******************************************/
  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "gauge"; /*!< Block type. */

  /******************************************/
  /*!
      @brief  Returns width of block.
      @return Block width.
  */
  /******************************************/
  int _width() { return width; }

  /******************************************/
  /*!
      @brief  Returns height of block.
      @return Block height.
  */
  /******************************************/
  int _height() { return height; }

  /******************************************/
  /*!
      @brief  Returns block's row location
      on an Adafruit IO dashboard.
      @return Adafruit IO dashboard row.
  */
  /******************************************/
  int _row() { return row; }

  /******************************************/
  /*!
      @brief  Returns block's column location
      on an Adafruit IO dashboard.
      @return Adafruit IO dashboard column
  */
  /******************************************/
  int _column() { return column; }
};

#endif // ADAFRUITIO_GAUGEBLOCK_H
