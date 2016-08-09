//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifdef ARDUINO_ARCH_AVR

#include "AdafruitIO_FONA.h"

AdafruitIO_FONA::AdafruitIO_FONA(const char *user, const char *key):AdafruitIO(user, key)
{
  _serial = new SoftwareSerial(FONA_TX, FONA_RX);
  _fona = new Adafruit_FONA(FONA_RST);
  _mqtt = new Adafruit_MQTT_FONA(_fona, _host, _port);
  _packetread_timeout = 1000;
}

AdafruitIO_FONA::AdafruitIO_FONA(const __FlashStringHelper *user, const __FlashStringHelper *key):AdafruitIO(user, key)
{
  _serial = new SoftwareSerial(FONA_TX, FONA_RX);
  _fona = new Adafruit_FONA(FONA_RST);
  _mqtt = new Adafruit_MQTT_FONA(_fona, _host, _port);
  _packetread_timeout = 1000;
}

void AdafruitIO_FONA::setAPN(FONAFlashStringPtr apn, FONAFlashStringPtr username=0, FONAFlashStringPtr password=0)
{
  _fona->setGPRSNetworkSettings(apn, username, password);
}

void AdafruitIO_FONA::_connect()
{

  // set software serial baud rate
  _serial->begin(FONA_BAUD);

  // if fona can't be found, bail
  if(! _fona->begin(*_serial)) {
    _status = AIO_NET_CONNECT_FAILED;
    return;
  }

  // disable cme error reporting
  _serial->println("AT+CMEE=2");

  _status = AIO_NET_DISCONNECTED;

}

aio_status_t AdafruitIO_FONA::networkStatus()
{

  // return if in a failed state
  if(_status == AIO_NET_CONNECT_FAILED)
    return _status;

  // if we are connected, return
  if(_fona->GPRSstate())
   return AIO_NET_CONNECTED;

  // wait for connection to network
  if(_fona->getNetworkStatus() != 1)
    return AIO_NET_DISCONNECTED;

  _fona->enableGPRS(true);
  return AIO_NET_CONNECTED;

}

#endif // ARDUINO_ARCH_AVR
