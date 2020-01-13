/*!
 * @file AdafruitIO_Block.h
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
#ifndef ADAFRUITIO_BLOCK_H
#define ADAFRUITIO_BLOCK_H

#include "AdafruitIO_Definitions.h"
#include "Arduino.h"

class AdafruitIO_Dashboard;
class AdafruitIO_Feed;

/**************************************************************************/
/*!
    @brief  Class for interacting with and creating Adafruit IO Dashboard
            blocks.
*/
/**************************************************************************/
class AdafruitIO_Block {

public:
  AdafruitIO_Block(AdafruitIO_Dashboard *d, AdafruitIO_Feed *f);
  ~AdafruitIO_Block();

  int width = 2;  /*!< Dashboard block width. */
  int height = 2; /*!< Dashboard block height. */
  int row = 0;    /*!< Row location of block on dashboard. */
  int column = 0; /*!< Column location of block on dashboard. */

  virtual String properties();
  String dimensions();

  virtual const char *type();

  bool save();

protected:
  AdafruitIO_Dashboard
      *_dashboard;        /*!< Instance of an Adafruit IO Dashboard. */
  AdafruitIO_Feed *_feed; /*!< Instance of an Adafruit IO Feed. */

  const char *_visual_type; /*!< Block type. */

  /******************************************/
  /*!
      @brief  Returns width of block.
      @return Block width.
  */
  /******************************************/
  virtual int _width() { return width; }

  /******************************************/
  /*!
      @brief  Returns height of block.
      @return Block height.
  */
  /******************************************/
  virtual int _height() { return height; }

  /******************************************/
  /*!
      @brief  Returns block's row location
      on an Adafruit IO dashboard.
      @return Adafruit IO dashboard row.
  */
  /******************************************/
  virtual int _row() { return row; }

  /******************************************/
  /*!
      @brief  Returns block's column location
      on an Adafruit IO dashboard.
      @return Adafruit IO dashboard column
  */
  /******************************************/
  virtual int _column() { return column; }
};

#endif // ADAFRUITIO_BLOCK_H
