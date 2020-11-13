// Adafruit IO Publish & Subscribe, Digital Input and Output Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Modified by Brent Rubell for Adafruit Industries
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

// Button Pin
#define BUTTON_PIN 0

// LED Pin
#define LED_PIN LED_BUILTIN

// button state
bool btn_state = false;
bool prv_btn_state = false;

// set up the 'led' feed
AdafruitIO_Feed *led = io.feed("led");

// set up the 'button' feed
AdafruitIO_Feed *button = io.feed("button");

void setup() {

  // set button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // set LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  led->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  led->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the btn_state state of the button.
  if(digitalRead(BUTTON_PIN) == LOW)
    btn_state = false;
  else
    btn_state = true;

  // return if the btn state hasn't changed
  if(btn_state == prv_btn_state)
    return;

  // save the btn_state state to the 'button' feed on adafruit io
  Serial.print("sending button -> "); Serial.println(btn_state);
  button->save(btn_state);

  // store last button state
  prv_btn_state = btn_state;

}

// this function is called whenever a 'led' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");

  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

  digitalWrite(LED_PIN, data->toPinLevel());
}