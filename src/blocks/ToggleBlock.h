/*!
 * @file ToggleBlock.h
 *
 * This is part of the Adafruit IO library for the Arduino platform.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Tony DiCola, Todd Treece for Adafruit Industries
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
#ifndef ADAFRUITIO_TOGGLEBLOCK_H
#define ADAFRUITIO_TOGGLEBLOCK_H

#include "AdafruitIO_Block.h"

/**************************************************************************/
/*!
    @brief  Class for creating an Adafruit IO Dashboard Toggle Block.
*/
/**************************************************************************/
class ToggleBlock : public AdafruitIO_Block {

public:
  ToggleBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~ToggleBlock();

  const char *onText; /*!< Text to display if the switch is in the on state. */
  const char
      *offText; /*!< Text to display if the switch is in the off state. */

  int height = 2; /*!< Dashboard block height. */
  int width = 4;  /*!< Dashboard block width. */

  String properties();

  /******************************************/
  /*!
      @brief  Returns block type
      @return Block type.
  */
  /******************************************/
  const char *type() { return _visual_type; }

protected:
  const char *_visual_type = "toggle_button"; /*!< Block type. */

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

#endif // ADAFRUITIO_TOGGLEBLOCK_H
