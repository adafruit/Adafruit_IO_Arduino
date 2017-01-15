// Adafruit IO Location Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// this value integer will hold the current count value for our sketch
int value = 0;

// these double values will hold our fake GPS data
double lat = 42.331427;
double lon = -83.045754;
double ele = 0;

// set up the 'location' feed
AdafruitIO_Feed *location = io.feed("location");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print(F("Connecting to Adafruit IO"));

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the location feed.
  location->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(F("."));
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // process messages and keep connection alive
  io.run();

  Serial.println(F("----- sending -----"));
  Serial.print(F("value: "));
  Serial.println(value);
  Serial.print(F("lat: "));
  Serial.println(lat, 6);
  Serial.print(F("lon: "));
  Serial.println(lon, 6);
  Serial.print(F("ele: "));
  Serial.println(ele, 2);

  // save value and location data to the
  // 'location' feed on Adafruit IO
  location->save(value, lat, lon, ele);

 // shift all values (for demo purposes)
  value += 1;
  lat -= 0.01;
  lon += 0.02;
  ele += 1;

  // wait one second (1000 milliseconds == 1 second)
  delay(1000);

}

void handleMessage(AdafruitIO_Data *data) {

  // since we sent an int, we can use toInt()
  // to get the int value from the received IO
  // data.
  int received_value = data->toInt();

  // the lat() lon() and ele() methods
  // will allow you to get the double values
  // for the location data sent by IO
  double received_lat = data->lat();
  double received_lon = data->lon();
  double received_ele = data->ele();

  // print out the received values
  Serial.println(F("----- received -----"));
  Serial.print(F("value: "));
  Serial.println(received_value);
  Serial.print(F("lat: "));
  Serial.println(received_lat, 6);
  Serial.print(F("lon: "));
  Serial.println(received_lon, 6);
  Serial.print(F("ele: "));
  Serial.println(received_ele, 2);

}
