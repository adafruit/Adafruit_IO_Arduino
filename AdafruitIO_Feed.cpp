#include "AdafruitIO_Feed.h"
#include "AdafruitIO.h"

AdafruitIO_Feed::AdafruitIO_Feed(AdafruitIO *io, const char *name)
{

  _io = io;
  _name = name;

}

AdafruitIO_Feed::AdafruitIO_Feed(AdafruitIO *io, const __FlashStringHelper *name)
{

  _io = io;
  _name = (const char*)name;

}

void AdafruitIO_Feed::onMessage(SubscribeCallbackBufferType cb)
{


  if(! _sub)
    _init();

  _io->_mqtt->subscribe(_sub);
  _sub->setCallback(cb);

}

void AdafruitIO_Feed::onMessage(SubscribeCallbackDoubleType cb)
{

  if(! _sub)
    _init();

  _io->_mqtt->subscribe(_sub);
  _sub->setCallback(cb);

}

void AdafruitIO_Feed::onMessage(SubscribeCallbackUInt32Type cb)
{

  if(! _sub)
    _init();

  _io->_mqtt->subscribe(_sub);
  _sub->setCallback(cb);

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

void AdafruitIO_Feed::_init()
{

  // dynamically allocate memory for topic
  _topic = (char *) malloc(sizeof(char) * (strlen(_io->_username) + strlen(_name) + 4)); // 4 extra is for /f/ & null termination

  if(_topic) {

    // build topic string
    strcpy(_topic, _io->_username);
    strcat(_topic, "/f/");
    strcat(_topic, _name);

    // setup subscription
    _sub = new Adafruit_MQTT_Subscribe(_io->_mqtt, _topic);
    _pub = new Adafruit_MQTT_Publish(_io->_mqtt, _topic);

  } else {

    // malloc failed
    _topic = 0;
    _sub = 0;
    _pub = 0;

  }

}
