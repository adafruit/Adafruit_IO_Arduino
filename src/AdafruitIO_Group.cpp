/*!
 * @file AdafruitIO_Group.cpp
 *
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2016 Adafruit Industries
 * Authors: Tony DiCola, Todd Treece
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 *
 */
#include "AdafruitIO_Group.h"
#include "AdafruitIO.h"

/**************************************************************************/
/*!
    @brief    Creates a new instance of an Adafruit IO Group.
    @param    *io
              Reference to AdafruitIO.
    @param    *n
              Valid group name.
*/
/**************************************************************************/
AdafruitIO_Group::AdafruitIO_Group(AdafruitIO *io, const char *n)
    : AdafruitIO_MQTT() {
  _io = io;
  name = n;
  owner = _io->_username;

  _init();
}

/**************************************************************************/
/*!
    @brief  Adafruit IO Group destructor.
*/
/**************************************************************************/
AdafruitIO_Group::~AdafruitIO_Group() {
  if (_sub)
    delete _sub;

  if (_pub)
    delete _pub;

  if (_get_pub)
    delete _get_pub;

  if (data)
    delete data;

  if (_topic)
    free(_topic);

  if (_get_topic)
    free(_get_topic);

  if (_group_url)
    free(_group_url);

  if (_create_url)
    free(_create_url);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, char *value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, bool value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, String value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, int value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, unsigned int value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, long value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, unsigned long value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, float value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Sets value of Adafruit IO Group.
    @param    feed
              Adafruit IO feed name.
    @param    value
              Adafruit IO feed value.
*/
/**************************************************************************/
void AdafruitIO_Group::set(const char *feed, double value) {
  AdafruitIO_Data *f = getFeed(feed);
  f->setValue(value);
}

/**************************************************************************/
/*!
    @brief    Updates value of Adafruit IO Group.
    @return   True if successfully published to group, False if data is
              NULL or if unable to successfully publish data to group.
*/
/**************************************************************************/
bool AdafruitIO_Group::save() {

  if (data == NULL)
    return false;

  char csv[150];
  AdafruitIO_Data *cur_data = data;

  strcpy(csv, "");

  while (cur_data != NULL) {

    strcat(csv, cur_data->feedName());
    strcat(csv, ",");
    strcat(csv, cur_data->toChar());
    strcat(csv, "\n");

    cur_data = cur_data->next_data;
  }

  return _pub->publish(csv);
}

/**************************************************************************/
/*!
    @brief    Publishes null value ("\0") to Adafruit IO Group
              https://io.adafruit.com/api/docs/mqtt.html#retained-values
    @return   True if successfully published to group, False otherwise.
*/
/**************************************************************************/
bool AdafruitIO_Group::get() { return _get_pub->publish("\0"); }

/**************************************************************************/
/*
    @brief    Helper function to compare strings case-insensitively
    @return   True if strings are equal (ignoring case)
*/
/**************************************************************************/
bool strsame_nocase(const char *str1, const char *str2) {
  while ( *str1 && *str2 && tolower(*str1) == tolower(*str2) ) {
    ++str1;
    ++str2;
  }
  return tolower(*str1) == tolower(*str2);
}

/**************************************************************************/
/*!
    @brief    Obtains data from feed within group.
    @param    feed
              Existing Adafruit IO Feed.
    @return   cur_data  Data from feed within group
              data      Adafruit IO Feed does not exist in group. Data is
                        the value of a generated feed, feed, within group.
              NULL      If unable to return data.
*/
/**************************************************************************/
AdafruitIO_Data *AdafruitIO_Group::getFeed(const char *feed) {
  if (data == NULL) {
    data = new AdafruitIO_Data(feed);
    return data;
  }

  AdafruitIO_Data *cur_data = data;

  while (cur_data != NULL) {

    if (strsame_nocase(cur_data->feedName(), feed)) {
      return cur_data;
    }

    if (!cur_data->next_data) {
      cur_data->next_data = new AdafruitIO_Data(feed);
      return cur_data->next_data;
    }

    cur_data = cur_data->next_data;
  }

  return NULL;
}

/**************************************************************************/
/*!
    @brief    Sets up Adafruit IO callback to monitor incoming
              new data in group.
    @param    cb
              An function to be called if group receives new data.
*/
/**************************************************************************/
void AdafruitIO_Group::onMessage(AdafruitIODataCallbackType cb) {
  if (_groupCallback == NULL) {
    _groupCallback = new AdafruitIOGroupCallback(cb);
    return;
  }

  AdafruitIOGroupCallback *cur_cb = _groupCallback;

  while (cur_cb != NULL) {

    if (!cur_cb->next_cb) {
      cur_cb->next_cb = new AdafruitIOGroupCallback(cb);
      return;
    }

    cur_cb = cur_cb->next_cb;
  }
}

/**************************************************************************/
/*!
    @brief    Sets up Adafruit IO callback to monitor incoming
              new data in group's feed, feed.
    @param    feed
              An Adafruit IO Feed within Group.
    @param    cb
              An function to be called if group receives new data.
*/
/**************************************************************************/
void AdafruitIO_Group::onMessage(const char *feed,
                                 AdafruitIODataCallbackType cb) {
  if (_groupCallback == NULL) {
    _groupCallback = new AdafruitIOGroupCallback(feed, cb);
    return;
  }

  AdafruitIOGroupCallback *cur_cb = _groupCallback;

  while (cur_cb != NULL) {

    if (strsame_nocase(cur_cb->feed, feed)) {
      return;
    }

    if (!cur_cb->next_cb) {
      cur_cb->next_cb = new AdafruitIOGroupCallback(feed, cb);
      return;
    }

    cur_cb = cur_cb->next_cb;
  }
}

/**************************************************************************/
/*!
    @brief    Adafruit IO Group subscription function callback.
    @param    d
              Name of feed within group.
*/
/**************************************************************************/
void AdafruitIO_Group::call(AdafruitIO_Data *d) {
  // uint8_t i;

  if (_groupCallback == NULL) {
    return;
  }

  AdafruitIOGroupCallback *cur_cb = _groupCallback;

  while (cur_cb) {

    if (cur_cb->feed == NULL || strsame_nocase(cur_cb->feed, d->feedName())) {
      cur_cb->dataCallback(d);
    }

    cur_cb = cur_cb->next_cb;
  }
}

/**************************************************************************/
/*!
    @brief    Checks for new value within Adafruit IO group.
    @param    val
              Value to send to Adafruit IO group.
    @param    len
              Length of Adafruit IO value.
*/
/**************************************************************************/
void AdafruitIO_Group::subCallback(char *val, uint16_t len) {

  char *line;
  char *name;
  char *value;

  if (_groupCallback == NULL)
    return;

  while ((line = strtok_r(val, "\n", &val)) != NULL) {

    name = strtok_r(line, ",", &line);

    // couldn't grab name from line, move on
    if (!name)
      continue;

    // don't handle location for now
    if (strcmp(name, "location") == 0)
      continue;

    value = strtok_r(line, ",", &line);

    // no value? move on
    if (!value)
      continue;

    AdafruitIO_Data *feed = getFeed(name);

    // we couldn't get the data, move on
    if (!feed)
      continue;

    feed->setValue(value);
    call(feed);
  }
}

/**************************************************************************/
/*!
    @brief    Sets up locational metadata.
    @param    lat
              Desired latitude.
    @param    lon
              Desired longitude.
    @param    ele
              Desired elevation.
*/
/**************************************************************************/
void AdafruitIO_Group::setLocation(double lat, double lon, double ele) {
  // uint8_t i;

  if (data == NULL) {
    return;
  }

  AdafruitIO_Data *cur_data = data;

  while (cur_data) {
    cur_data->setLocation(lat, lon, ele);
    cur_data = cur_data->next_data;
  }
}

/**************************************************************************/
/*!
    @brief    Checks if Adafruit IO Group exists.
              https://io.adafruit.com/api/docs/#get-group
    @return   True if successful, otherwise False.
*/
/**************************************************************************/
bool AdafruitIO_Group::exists() {
  _io->_http->beginRequest();
  _io->_http->get(_group_url);
  _io->_http->sendHeader("X-AIO-Key", _io->_key);
  _io->_http->endRequest();

  int status = _io->_http->responseStatusCode();
  _io->_http->responseBody(); // needs to be read even if not used
  return status == 200;
}

/**************************************************************************/
/*!
    @brief    Creates new Adafruit IO Group.
              https://io.adafruit.com/api/docs/#create-group
    @return   True if successful, otherwise False.
*/
/**************************************************************************/
bool AdafruitIO_Group::create() {
  String body = "name=";
  body += name;

  _io->_http->beginRequest();
  _io->_http->post(_create_url);

  _io->_http->sendHeader("Content-Type", "application/x-www-form-urlencoded");
  _io->_http->sendHeader("Content-Length", body.length());
  _io->_http->sendHeader("X-AIO-Key", _io->_key);

  // the following call to endRequest
  // should be replaced by beginBody once the
  // Arduino HTTP Client Library is updated
  // _io->_http->beginBody();
  _io->_http->endRequest();

  _io->_http->print(body);
  _io->_http->endRequest();

  int status = _io->_http->responseStatusCode();
  _io->_http->responseBody(); // needs to be read even if not used
  return status == 201;
}

/**************************************************************************/
/*!
    @brief    Initialize MQTT topics and REST URLs for Adafruit IO groups.
*/
/**************************************************************************/
void AdafruitIO_Group::_init() {

  // dynamically allocate memory for mqtt topic and REST URLs
  _topic = (char *)malloc(
      sizeof(char) * (strlen(owner) + strlen(name) +
                      8)); // 8 extra chars for /g/, /csv & null termination
  _get_topic = (char *)malloc(
      sizeof(char) *
      (strlen(owner) + strlen(name) +
       12)); // 12 extra chars for /f/, /csv/get & null termination
  _group_url =
      (char *)malloc(sizeof(char) * (strlen(owner) + strlen(name) +
                                     16)); // 16 extra for api path & null term
  _create_url = (char *)malloc(
      sizeof(char) * (strlen(owner) + 15)); // 15 extra for api path & null term

  data = 0;

  if (_topic && _create_url && _group_url) {

    // build topic string
    strcpy(_topic, owner);
    strcat(_topic, "/g/");
    strcat(_topic, name);
    strcat(_topic, "/csv");

    // build feed url string
    strcpy(_group_url, "/api/v2/");
    strcat(_group_url, owner);
    strcat(_group_url, "/groups/");
    strcat(_group_url, name);

    // build create url string
    strcpy(_create_url, "/api/v2/");
    strcat(_create_url, owner);
    strcat(_create_url, "/groups");

    // build /get topic string
    strcpy(_get_topic, owner);
    strcat(_get_topic, "/g/");
    strcat(_get_topic, name);
    strcat(_get_topic, "/csv/get");

    // setup subscription
    _sub = new Adafruit_MQTT_Subscribe(_io->_mqtt, _topic);
    _pub = new Adafruit_MQTT_Publish(_io->_mqtt, _topic);
    _get_pub = new Adafruit_MQTT_Publish(_io->_mqtt, _get_topic);
    _io->_mqtt->subscribe(_sub);

    _sub->setCallback(this, &AdafruitIO_MQTT::subCallback);

  } else {

    // malloc failed
    _topic = 0;
    _get_topic = 0;
    _create_url = 0;
    _group_url = 0;
    _sub = 0;
    _pub = 0;
    _get_pub = 0;
  }
}
