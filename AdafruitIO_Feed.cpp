#include "AdafruitIO_Feed.h"
#include "AdafruitIO.h"

AdafruitIO_Feed::AdafruitIO_Feed(AdafruitIO *io, const char *n)
{
  _io = io;
  name = n;
  _sub = 0;
  _pub = 0;
}

AdafruitIO_Feed::AdafruitIO_Feed(AdafruitIO *io, const __FlashStringHelper *n)
{
  _io = io;
  name = (const char*)n;
  _sub = 0;
  _pub = 0;
}

void AdafruitIO_Feed::onMessage(AdafruitIODataCallbackType cb)
{
  if(! _sub)
    _init();

  _dataCallback = cb;
  _io->_mqtt->subscribe(_sub);

  _sub->setCallback(this, &AdafruitIO_Feed::subCallback);
}

bool AdafruitIO_Feed::save(const char *s)
{
  if(! _pub)
    _init();

  return _pub->publish(s);
}

bool AdafruitIO_Feed::save(double f, uint8_t precision)
{
  if(! _pub)
    _init();

  return _pub->publish(f, precision);
}

bool AdafruitIO_Feed::save(int32_t i)
{
  if(! _pub)
    _init();

  return _pub->publish(i);
}

bool AdafruitIO_Feed::save(uint32_t i)
{
  if(! _pub)
    _init();

  return _pub->publish(i);
}

bool AdafruitIO_Feed::save(uint8_t *b, uint16_t bLen)
{
  if(! _pub)
    _init();

  return _pub->publish(b, bLen);
}

void AdafruitIO_Feed::subCallback(char *val, uint16_t len)
{
  if(! _dataCallback)
    return;

  _data->setCSV(val);
  _dataCallback(_data);
}

void AdafruitIO_Feed::_init()
{

  // dynamically allocate memory for topic
  _sub_topic = (char *) malloc(sizeof(char) * (strlen(_io->_username) + strlen(name) + 8)); // 8 extra chars for /f/, /csv & null termination
  _pub_topic = (char *) malloc(sizeof(char) * (strlen(_io->_username) + strlen(name) + 4)); // 4 extra chars for /f/ & null termination

  // init feed data
  _data = new AdafruitIO_Data(this);

  if(_pub_topic && _sub_topic) {

    // build topic string
    strcpy(_pub_topic, _io->_username);
    strcat(_pub_topic, "/f/");
    strcat(_pub_topic, name);

    strcpy(_sub_topic, _pub_topic);
    strcat(_sub_topic, "/csv");

    // setup subscription
    _sub = new Adafruit_MQTT_Subscribe(_io->_mqtt, _sub_topic);
    _pub = new Adafruit_MQTT_Publish(_io->_mqtt, _pub_topic);

  } else {

    // malloc failed
    _sub_topic = 0;
    _pub_topic = 0;
    _sub = 0;
    _pub = 0;

  }

}
