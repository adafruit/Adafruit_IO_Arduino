/*!
 * @file AdafruitIO_Feed.h
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
#ifndef ADAFRUITIO_FEED_H
#define ADAFRUITIO_FEED_H

#include "AdafruitIO_Data.h"
#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_MQTT.h"
#include "Adafruit_MQTT.h"
#include "Arduino.h"

// forward declaration
class AdafruitIO;

/**************************************************************************/
/*!
    @brief  Class that provides methods for interfacing with
            Adafruit IO feed topics.
            https://io.adafruit.com/api/docs/mqtt.html#mqtt-topics
*/
/**************************************************************************/
class AdafruitIO_Feed : public AdafruitIO_MQTT {

public:
  AdafruitIO_Feed(AdafruitIO *io, const char *name);
  AdafruitIO_Feed(AdafruitIO *io, const char *name, const char *owner);

  ~AdafruitIO_Feed();

  bool save(char *value, double lat = 0, double lon = 0, double ele = 0);
  bool save(bool value, double lat = 0, double lon = 0, double ele = 0);
  bool save(String value, double lat = 0, double lon = 0, double ele = 0);
  bool save(int value, double lat = 0, double lon = 0, double ele = 0);
  bool save(unsigned int value, double lat = 0, double lon = 0, double ele = 0);
  bool save(long value, double lat = 0, double lon = 0, double ele = 0);
  bool save(unsigned long value, double lat = 0, double lon = 0,
            double ele = 0);
  bool save(float value, double lat = 0, double lon = 0, double ele = 0,
            int precision = 6);
  bool save(double value, double lat = 0, double lon = 0, double ele = 0,
            int precision = 6);

  bool get();

  bool exists();
  bool create();

  void setLocation(double lat, double lon, double ele = 0);

  void onMessage(AdafruitIODataCallbackType cb);
  void subCallback(char *val, uint16_t len);

  const char *name;  /*!< Adafruit IO feed name. */
  const char *owner; /*!< Adafruit IO feed owner. */

  AdafruitIO_Data *lastValue(); /*!< Last value sent to Adafruit IO feed. */
  AdafruitIO_Data *data;        /*!< Adafruit IO feed data record. */

private:
  AdafruitIODataCallbackType
      _dataCallback; /*!< Callback from onMessage containing data. */

  void _init();

  char *_topic;      /*!< MQTT Topic URL */
  char *_get_topic;  /*!< /get topic string */
  char *_create_url; /*!< create URL string */
  char *_feed_url;   /*!< feed URL string */

  Adafruit_MQTT_Subscribe *_sub;   /*!< MQTT subscription for _topic. */
  Adafruit_MQTT_Publish *_pub;     /*!< MQTT publish for _topic. */
  Adafruit_MQTT_Publish *_get_pub; /*!< MQTT publish to _get_topic. */

  AdafruitIO *_io;        /*!< An instance of AdafruitIO. */
  AdafruitIO_Data *_data; /*!< An instance of AdafruitIO_Data. */
};

#endif // ADAFRUITIO_FEED_H
