//
// Copyright (c) 2015-2016 Adafruit Industries
// Authors: Tony DiCola, Todd Treece
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//
#ifdef ARDUINO_ARCH_AVR

#include "AdafruitIO_FONA.h"

AdafruitIO_FONA::AdafruitIO_FONA(const char *apn, const char *apn_user, const char *apn_pass):AdafruitIO()
{
  _apn = apn;
  _apn_user = apn_user;
  _apn_pass = apn_pass;
  _serial = new SoftwareSerial(FONA_TX, FONA_RX);
  _fona = new Adafruit_FONA(FONA_RST);
  _mqtt = new Adafruit_MQTT_FONA(_fona, _host, _port);
}

AdafruitIO_FONA::AdafruitIO_FONA(const __FlashStringHelper *apn, const __FlashStringHelper *apn_user, const __FlashStringHelper *apn_pass):AdafruitIO()
{
  _apn = (const char*)apn;
  _apn_user = (const char*)apn_user;
  _apn_pass = (const char*)apn_pass;
  _serial = new SoftwareSerial(FONA_TX, FONA_RX);
  _fona = new Adafruit_FONA(FONA_RST);
  _mqtt = new Adafruit_MQTT_FONA(_fona, _host, _port);
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

  // set apn info
  // _fona->setGPRSNetworkSettings(_apn, _apn_user, _apn_pass);

  _fona->enableGPRS(true);
  return AIO_NET_CONNECTED;

}

#endif // ARDUINO_ARCH_AVR
