// Adafruit IO ADT7410 Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Ladyada and Brent Rubell for Adafruit Industries
// Copyright (c) 2019 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

// time between sending data to adafruit io, in minutes
#define MESSAGE_WAIT_SEC (1 * 60)
/************************ Example Starts Here *******************************/
#include <Wire.h>
// adt7410 sensor
#include "Adafruit_ADT7410.h"
// featherwing oled
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

// Create the OLED display object
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

// Create the ADT7410 temperature sensor object
Adafruit_ADT7410 tempsensor = Adafruit_ADT7410();

// set up the 'temperature' feed
AdafruitIO_Feed *huzzah_temperature = io.feed("temperature");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.println("Adafruit IO ADT7410 + OLED");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x49) for example
  if (!tempsensor.begin()) {
    Serial.println("Couldn't find ADT7410!");
    while (1);
  }

  // sensor takes 250 ms to get first readings
  delay(250);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Connecting to IO...");
  display.display();


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

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();

  Serial.print("Temp: ");
  Serial.print(c);
  Serial.println("C");

  // clear the display
  display.clearDisplay();
  display.display();

  // print to display
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Temp:");
  display.print(c);
  
  // send data to adafruit io
  display.setCursor(15, 20);
  display.setTextSize(1);
  display.print("Sending...");
  display.display();
  Serial.println("Sending to Adafruit IO");
  delay(1000);
  huzzah_temperature->save(c, 0, 0, 0, 6);

  // sent to IO
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Temp:");
  display.print(c);
  display.setTextSize(1);
  display.setCursor(15, 20);
  display.print("Sending...Done!");
  display.display();

  Serial.print("Waiting "); Serial.print(MESSAGE_WAIT_SEC); Serial.println(" seconds");
  // wait 15 minutes between sends
  for (int i=0; i<MESSAGE_WAIT_SEC; i++) {
    delay(1000);
  }
}
