//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright (c) 2015-2016 Adafruit Industries
// Author: Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifndef ADAFRUITIO_GROUP_H
#define ADAFRUITIO_GROUP_H

#include "AdafruitIO_Data.h"
#include "AdafruitIO_Definitions.h"
#include "AdafruitIO_MQTT.h"
#include "Adafruit_MQTT.h"
#include "Arduino.h"

// forward declaration
class AdafruitIO;

/**************************************************************************/
/*!
    @brief  Class for interacting with Adafruit IO Grouped Feeds
            https://io.adafruit.com/api/docs/mqtt.html#group-topics
*/
/**************************************************************************/
class AdafruitIO_Group : public AdafruitIO_MQTT {

public:
  AdafruitIO_Group(AdafruitIO *io, const char *name);
  ~AdafruitIO_Group();

  void set(const char *feed, char *value);
  void set(const char *feed, bool value);
  void set(const char *feed, String value);
  void set(const char *feed, int value);
  void set(const char *feed, unsigned int value);
  void set(const char *feed, long value);
  void set(const char *feed, unsigned long value);
  void set(const char *feed, float value);
  void set(const char *feed, double value);

  bool save();
  bool get();

  void setLocation(double lat = 0, double lon = 0, double ele = 0);

  bool exists();
  bool create();

  void onMessage(AdafruitIODataCallbackType cb);
  void onMessage(const char *feed, AdafruitIODataCallbackType cb);

  void subCallback(char *val, uint16_t len);
  void call(AdafruitIO_Data *d);

  const char *name;  /*!< Adafruit IO group name. */
  const char *owner; /*!< Adafruit IO username of group owner. */

  AdafruitIO_Data *data; /*!< Adafruit IO data record. */
  AdafruitIO_Data *getFeed(const char *feed);

private:
  void _init();

  char *_topic;      /*!< MQTT topic URL.. */
  char *_get_topic;  /*!< /get topic string. */
  char *_create_url; /*!< Create URL string. */
  char *_group_url;  /*!< Group URL string. */

  Adafruit_MQTT_Subscribe *_sub;   /*!< MQTT subscription for _topic. */
  Adafruit_MQTT_Publish *_pub;     /*!< MQTT publish for _topic. */
  Adafruit_MQTT_Publish *_get_pub; /*!< MQTT publish to _get_topic. */

  AdafruitIO *_io; /*!< An instance of AdafruitIO. */
  AdafruitIOGroupCallback
      *_groupCallback; /*!< An instance of AdafruitIOGroupCallback */

  double _lat, _lon, _ele; /*!< latitude, longitude, elevation metadata. */
};

#endif // ADAFRUITIO_GROUP_H
