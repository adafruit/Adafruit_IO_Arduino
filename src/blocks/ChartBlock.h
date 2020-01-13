/*!
 * @file ChartBlock.h
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
#ifndef ADAFRUITIO_CHARTBLOCK_H
#define ADAFRUITIO_CHARTBLOCK_H

#include "AdafruitIO_Block.h"

/**************************************************************************/
/*!
    @brief  Class for interacting with the Adafruit IO Dashboard
            Chart Block.
*/
/**************************************************************************/
class ChartBlock : public AdafruitIO_Block {

public:
  ChartBlock(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~ChartBlock();

  /******************************************/
  /*!
      @brief  Returns block type
      @return Block type.
  */
  /******************************************/
  const char *type() { return _visual_type; }

  int historyHours; /*!< Amount of hours to store the chart's history for. */
  const char *xAxisLabel; /*!< Chart's x-axis label. */
  const char *yAxisLabel; /*!< Chart's y-axis label. */
  int yAxisMin;           /*!< Chart's y-axis minimum. */
  int yAxisMax;           /*!< Chart's y-axis maximum. */

  int width = 6;  /*!< Dashboard block width. */
  int height = 4; /*!< Dashboard block height. */

  String properties();

protected:
  const char *_visual_type = "line_chart"; /*!< Block type. */

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

#endif // ADAFRUITIO_CHARTBLOCK_H
