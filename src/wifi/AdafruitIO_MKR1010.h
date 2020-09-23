/*!
 * @file AdafruitIO_MKR1010.h
 *
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) 2015-2016 Adafruit Industries
 * Authors: Tony DiCola, Todd Treece, Morgan Winters
 * Licensed under the MIT license.
 *
 * All text above must be included in any redistribution.
 */

#ifndef ADAFRUITIO_MKR1010_H
#define ADAFRUITIO_MKR1010_H

#if defined(ARDUINO_SAMD_MKR1010)

#include "AdafruitIO.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Arduino.h"
#include "SPI.h"
#include "WiFiNINA.h"
#include "WiFiSSLClient.h"

class AdafruitIO_MKR1010 : public AdafruitIO {

public:
  AdafruitIO_MKR1010(const char *user, const char *key, const char *ssid,
                     const char *pass);
  ~AdafruitIO_MKR1010();

  aio_status_t networkStatus();
  const char *connectionType();

protected:
  void _connect();
  void _disconnect();

  const char *_ssid;
  const char *_pass;

  WiFiSSLClient *_client;
};

#endif // ARDUINO_ARCH_SAMD

#endif // ADAFRUITIO_MKR1010_H
