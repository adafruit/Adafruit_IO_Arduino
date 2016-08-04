//
//         Adafruit IO Location Example
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

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect(IO_USERNAME, IO_KEY);

  // set up a message handler for the location feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  location->onMessage(handleMessage);

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

  Serial.println("----- sending -----");
  Serial.print("value: ");
  Serial.println(value);
  Serial.print("lat: ");
  Serial.println(lat, 6);
  Serial.print("lon: ");
  Serial.println(lon, 6);
  Serial.print("ele: ");
  Serial.println(ele, 2);

  // save value and location data to the 'location' feed on Adafruit IO
  location->save(value, lat, lon, ele);

  // increment all values (for demo purposes)
  value += 1;
  lat += 0.1;
  lon += 0.2;
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

  Serial.println("----- received -----");
  Serial.print("value: ");
  Serial.println(received_value);
  Serial.print("lat: ");
  Serial.println(received_lat, 6);
  Serial.print("lon: ");
  Serial.println(received_lon, 6);
  Serial.print("ele: ");
  Serial.println(received_ele, 2);

}
