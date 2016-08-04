//
//         Adafruit IO Basic Counter Example
//
//                        ▄████
//                      ▄███████
//                     █████████▌
//                    ███████████
//                   ████████████▌
//  ███████████████▄ ████████████▌
//   █████████████████████▀▀█████ ▄▄▄▄▄▄▄
//    ▐██████████████████   █████████████████▄▄
//      ▀█████████  ▀▀███  ██████████████████████
//        █████████▄▄  ▐████▀    ▐█████████████▀
//          ▀▀███████████████▄▄█████████████▀
//           ▄███████   ██  ▀████████████▀
//          ███████▀  ▄████  ▐█████▄
//         █████████████████▄▄██████▄
//        ███████████████████████████
//       ██████████████ ▐████████████▌
//      ▐██████████▀▀    ▀███████████▌
//      █████▀▀            ▀█████████▌
//                            ▀██████
//                               ▀███
//
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.
//

/************************* WiFi Access Point *********************************/

#define WIFI_SSID       "your_ssid"
#define WIFI_PASS       "your_pass"

/************************* Adafruit IO Setup ********************************/

#define IO_USERNAME    "your_username"
#define IO_KEY         "your_key"

/*************************** Client Setup ***********************************/

// The Adafruit IO WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056

// set up the wifi client using the supplied ssid & pass:
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(WIFI_SSID, WIFI_PASS);

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 0;

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("counter");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect(IO_USERNAME, IO_KEY);

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  counter->onMessage(handleMessage);

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

  // this should be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any data from
  // the server
  io.run();

  // save count to the 'bar' feed on Adafruit IO
  Serial.print("sending -> ");
  Serial.println(count);
  counter->save(count);

  // increment the count by 1
  count++;

  // wait one second (1000 milliseconds == 1 seconds)
  delay(1000);

}

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
