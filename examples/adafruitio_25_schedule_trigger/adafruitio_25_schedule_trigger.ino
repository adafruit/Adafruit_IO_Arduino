// Adafruit IO Schedule Trigger Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-scheduled-triggers/
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Brent Rubell for Adafruit Industries
// Copyright (c) 2020 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/


// Relay is connected to PyPortal's D3 connector
#define RELAY_POWER_PIN 3

// Set up the 'relay feed'
AdafruitIO_Feed *relay = io.feed("relay");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the 'relay' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io
  relay->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  // Get the last known value from the feed
  relay->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'relay' feed message
// is received from Adafruit IO. it was attached to
// the 'relay' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("feed received new data <- ");
  Serial.println(data->toChar());

  // Check to see if the morning scheduled trigger has executed
  if (strcmp(data->toChar(), "morning") == 0) {
      Serial.println("Turning lights ON");
      digitalWrite(RELAY_POWER_PIN, HIGH);
  }
  // Check to see if the evening scheduled trigger has executed
  else if (strcmp(data->toChar(), "night") == 0) {
      Serial.println("Turning lights OFF");
      digitalWrite(RELAY_POWER_PIN, LOW);
  }
  else {
      Serial.println("Unexpected data received from Adafruit IO");
  }
}
