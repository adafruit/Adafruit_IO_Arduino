// Adafruit IO RGB LED Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-color
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016-2017 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// default PWM pins for ESP8266.
// you should change these to match PWM pins on other platforms.
#define RED_PIN   4
#define GREEN_PIN 5
#define BLUE_PIN  2

// set up the 'color' feed
AdafruitIO_Feed *color = io.feed("color");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'color' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  color->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  // set analogWrite range for ESP8266
  #ifdef ESP8266
    analogWriteRange(255);
  #endif

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever a 'color' message
// is received from Adafruit IO. it was attached to
// the color feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // print RGB values and hex value
  Serial.println("Received:");
  Serial.print("  - R: ");
  Serial.println(data->toRed());
  Serial.print("  - G: ");
  Serial.println(data->toGreen());
  Serial.print("  - B: ");
  Serial.println(data->toBlue());
  Serial.print("  - HEX: ");
  Serial.println(data->value());

  // invert RGB values for common anode LEDs
  analogWrite(RED_PIN, 255 - data->toRed());
  analogWrite(GREEN_PIN, 255 - data->toGreen());
  analogWrite(BLUE_PIN, 255 - data->toBlue());

}
