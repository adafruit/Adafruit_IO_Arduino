#include "AdafruitIO.h"

AdafruitIO::AdafruitIO(){}

void AdafruitIO::connect(const char *user, const char *key)
{

  _username = user;
  _key = key;

  _init();

}

void AdafruitIO::connect(const __FlashStringHelper *user, const __FlashStringHelper *key)
{

  _username = (const char*)user;
  _key = (const char*)key;

  _init();

}

void AdafruitIO::_init() {

  _last_ping = millis();

  // call child class connect
  _connect();

  // build error topic
  strcpy(_err_topic, _username);
  strcat(_err_topic, AIO_ERROR_TOPIC);

  // setup error sub
  _subscriptions[0] = new Adafruit_MQTT_Subscribe(_mqtt, _err_topic);

  // build throttle topic
  strcpy(_throttle_topic, _username);
  strcat(_throttle_topic, AIO_THROTTLE_TOPIC);

  // setup throttle sub
  _subscriptions[1] = new Adafruit_MQTT_Subscribe(_mqtt, _throttle_topic);

  _mqtt->subscribe(_subscriptions[0]);
  _mqtt->subscribe(_subscriptions[1]);

}

void AdafruitIO::setErrorHandler(AdafruitIOErrorCallbackType cb)
{
  _subscriptions[0]->setCallback(cb);
  _subscriptions[1]->setCallback(cb);
}

const __FlashStringHelper* AdafruitIO::statusText()
{

  switch(_status) {
    case AIO_IDLE: return F("Idle. Waiting for connect to be called...");
    case AIO_NET_DISCONNECTED: return F("Network disconnected.");
    case AIO_NET_CONNECT_FAILED: return F("Network connection failed.");
    case AIO_NET_CONNECTED: return F("Network connected.");
    case AIO_DISCONNECTED: return F("Disconnected from Adafruit IO.");
    case AIO_CONNECT_FAILED: return F("Adafruit IO connection failed.");
    case AIO_CONNECTED: return F("Adafruit IO connected.");
    default: return F("Unknown status code");
  }

}

void AdafruitIO::run()
{

  // bail if we aren't connected
  if(status() != AIO_CONNECTED)
    return;

  _mqtt->processPackets(1000);

  // ping to keep connection alive if needed
  if(millis() > (_last_ping + AIO_PING_INTERVAL)) {
    _mqtt->ping();
    _last_ping = millis();
  }

}
