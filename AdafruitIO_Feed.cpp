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

void AdafruitIO_Feed::_init()
{

  // dynamically allocate memory for topic
  _topic = (char *) malloc(sizeof(char) * (strlen(_io->_username) + strlen(_name) + 4)); // 4 extra is for /f/ & null termination

  if(_topic) {

    // build topic string
    strcpy(_topic, _io->_username);
    strcat(_topic, "/f/");
    strcat(_topic, _name);

    Serial.println(_topic);

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
