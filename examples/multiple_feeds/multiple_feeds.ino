// Adafruit IO Multiple Feed Example
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************* WiFi Access Point *********************************/

#define WIFI_SSID       "your_ssid"
#define WIFI_PASS       "your_pass"

/************************* Adafruit IO Setup ********************************/

#define IO_USERNAME    "your_username"
#define IO_KEY         "your_key"

/*************************** Client Setup ***********************************/

// set up the wifi client using the supplied ssid & pass:
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(WIFI_SSID, WIFI_PASS);

/************************ Example Starts Here *******************************/

// holds the current count value for our sketch
int count = 0;
// holds the boolean (true/false) state of the light
bool is_on = false;

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("counter");
// set up the 'light' feed
AdafruitIO_Feed *light = io.feed("light");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect(IO_USERNAME, IO_KEY);

  // set up a message handler for the counter feed.
  counter->onMessage(handleCount);

  // set up a message handler for the light feed.
  light->onMessage(handleLight);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // process messages and keep connection alive
  io.run();

  // print out the count we are sending to Adafruit IO
  Serial.println();
  Serial.print("sending -> count ");
  Serial.println(count);

  // save current count to 'counter' feed
  counter->save(count);

  // print out the light value we are sending to Adafruit IO
  Serial.print("sending -> light ");
  if(is_on)
    Serial.println("is on.\n");
  else
    Serial.println("is off.\n");


  // save state of light to 'light' feed
  light->save(is_on);

  // increment count value
  count++;

  // for the purpose of this demo, toggle the
  // light state based on the count value
  if((count % 2) == 0)
    is_on = true;
  else
    is_on = false;

  // wait two seconds (2000 milliseconds == 2 seconds)
  delay(2000);

}

// you can set a separate message handler for each
// feed (as we do in this example), or attach
// multiple feeds to the same meesage handler function.
void handleLight(AdafruitIO_Data *data) {

  // print out the received light value
  Serial.print("received <- light ");

  // use the isTrue helper to get the
  // boolean state of the light
  if(data->isTrue())
    Serial.println("is on.");
  else
    Serial.println("is off.");

}

void handleCount(AdafruitIO_Data *data) {

  // print out the received count value
  Serial.print("received <- count ");
  Serial.println(data->value());

}
