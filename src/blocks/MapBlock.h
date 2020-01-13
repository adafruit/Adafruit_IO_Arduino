/*!
 * @file MapBlock.h
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
#ifndef ADAFRUITIO_MAPBLOCK_H
#define ADAFRUITIO_MAPBLOCK_H

#include "AdafruitIO_Block.h"

/**************************************************************************/
/*!
    @brief  Class for interacting with the Adafruit IO Dashboard
            Map Block.
*/
/**************************************************************************/
class MapBlock : public AdafruitIO_Block {

public:
  MapBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~MapBlock();

  String props;     /*!< Map block properties. */
  int historyHours; /*!< Time displayed by map block in hours. */
  const char *tile; /*!< Map block title. */

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
  const char *_visual_type = "map"; /*!< Block type. */

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

#endif // ADAFRUITIO_MAPBLOCK_H
