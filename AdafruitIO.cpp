#include "AdafruitIO.h"

AdafruitIO::AdafruitIO(){}

void AdafruitIO::connect(const char *user, const char *key)
{
  _username = user;
  _key = key;
  _connect();
}

void AdafruitIO::connect(const __FlashStringHelper *user, const __FlashStringHelper *key)
{
  _username = (const char*)user;
  _key = (const char*)key;
  _connect();
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
