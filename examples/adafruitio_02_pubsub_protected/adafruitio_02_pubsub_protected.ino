// Adafruit IO Publish/Subscribe Example with Protection
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
// Comment out if you do not maintain an ssid.h file for your personal credentials.
// Then add your own credentials in the config.h tab. 
#include "ssid.h"   

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/
// This pub/sub example tests the status and reconnects if the network goes down.

// this int will hold the current count for our sketch
int count = 0;

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("counter");
// https://io.adafruit.com/api/docs/mqtt.html#username-errors
//AdafruitIO_Feed *throttles = io.feed("throttle");
//AdafruitIO_Feed *errors = io.feed("errors");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  setupIO();
}

void setupIO() {
  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com -- must be called before any other io calls!
  // calling io.status() first will make the subsequent connection attempt fail.
  io.connect();
  counter->onMessage(handleMessage);

  // wait for a connection
  unsigned long started = millis();
  while(io.status() < AIO_CONNECTED) {
    if(millis() - started > 30000){ 
      started = millis();
      io.connect();  // try again if you run out of patience
    }
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  counter->get();   // https://io.adafruit.com/api/docs/mqtt.html#using-the-get-topic
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("\nreceived <- ");
  Serial.println(data->value());
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  if(millis()%60000 > 30000){ 
    WiFi.disconnect();                          // Wifi will die in the top half of every minute
    delay(300);                                 // wait a while for the disaster to show...
  }
  Serial.print("\n\nTop of Loop!\nio.status: ");Serial.print(io.status()); 
  Serial.print(": ");                           Serial.print(io.statusText());    Serial.print("\n"); 
  Serial.print("io.networkStatus: ");           Serial.print(io.networkStatus()); Serial.print("\n"); 
  Serial.print("io.mqttStatus: ");              Serial.print(io.mqttStatus());    Serial.print("\n"); 
  Serial.print("WiFi.status: ");                Serial.print(WiFi.status());      Serial.print("\n"); 

  // Here's where we check the network and start over if it has lost connection
  if(io.status() < AIO_NET_CONNECTED){         
    Serial.print("Not Net Connected to IO!!! Reconnect!!!\n\n");
    count++;
    setupIO(); //Start IO all over again
  }

  Serial.print("Calling io.run()...");        // io.run() will hang if network disconnected 2019-11-16
  io.run();                                   // process messages and keep connection alive
  Serial.print("Done\n");
  
  // save count to the 'counter' feed on Adafruit IO
  Serial.print("sending -> ");
  Serial.print(count);
  if(counter->save(count)) Serial.print(" sent!");
  else Serial.print(" failed to send!");

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  // Adding the if statement allows you to generate a burst of faster saves
  // to generate some throttling events and see how the code responds.
  if(millis() < 90000 || millis() > 120000) delay(3000);
  else delay(5000);

}
