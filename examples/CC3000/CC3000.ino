// Adafruit IO REST API access with Adafruit CC3000
//
// Designed specifically to work with the Adafruit CC3000:
//  ----> https://www.adafruit.com/products/1469
//
// Adafruit invests time and resources providing this open source code, 
// please support Adafruit and open-source hardware by purchasing 
// products from Adafruit!
//
// Written by Tony DiCola for Adafruit Industries.  
// MIT license, all text above must be included in any redistribution.
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "Adafruit_IO_CC3000.h"


// Configure CC3000 pins.
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT  5  // VBAT & CS can be any digital pins.
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11

// Configure WiFi access point details.
#define WLAN_SSID       "...your SSID..."  // can't be longer than 32 characters!
#define WLAN_PASS       "...your password..."
#define WLAN_SECURITY   WLAN_SEC_WPA2  // Can be: WLAN_SEC_UNSEC, WLAN_SEC_WEP, 
                                       //         WLAN_SEC_WPA or WLAN_SEC_WPA2

// Configure Adafruit IO access.
#define AIO_KEY    "...your Adafruit IO key value ..."


// Setup the main CC3000 class, just like a normal CC3000 sketch.
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT);

// Create an Adafruit IO Client instance.  Notice that this needs to take a
// CC3000 object as the first parameter, and as the second parameter a
// default Adafruit IO key to use when accessing feeds (however each feed can
// override this default key value if required, see further below).
Adafruit_IO_CC3000 aio = Adafruit_IO_CC3000(cc3000, AIO_KEY);

// Finally create instances of Adafruit_IO_Feed objects, one per feed.  Do this
// by calling the getFeed function on the Adafruit_IO_FONA object and passing
// it at least the name of the feed, and optionally a specific AIO key to use
// when accessing the feed (the default is to use the key set on the
// Adafruit_IO_Client class).
Adafruit_IO_Feed testFeed = aio.getFeed("cc3ktestfeed");

// Alternatively to access a feed with a specific key:
//Adafruit_IO_Feed testFeed = aio.getFeed("cc3ktestfeed", "...cc3ktestfeed key...");

// Global state to increment a number and send it to the feed.
unsigned int count = 0;

#define halt(s) { Serial.println(F( s )); while(1);  }

void setup() {
  // Setup serial port access.
  Serial.begin(115200);

  Serial.println(F("Adafruit IO CC3000 test!"));

  // Initialise the CC3000 module.
  Serial.print(F("\nInit the CC3000..."));
  if (!cc3000.begin()) {
    halt("Failed");
  }

  // Check for compatible firmware.
  if (checkFirmwareVersion() < 0x113){
    halt("Wrong firmware version!");
  }

  // Delete any old connection data on the module
  Serial.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles()) {
    halt("Failed");
  }

  // Attempt to connect to an access point.
  Serial.print(F("\nAttempting to connect to ")); 
  Serial.print(WLAN_SSID); Serial.print(F("..."));
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY, 3)) {
    halt("Failed");
  }
  Serial.println(F("Connected!"));

  Serial.println(F("Requesting DHCP"));
  int retries = 10;
  while (!cc3000.checkDHCP())
  {
    delay(1000);
    retries--;
    if (!retries) {
      halt("Failed to get IP address!");
    }
  }  

  // Initialize the Adafruit IO client class (not strictly necessary with the
  // client class, but good practice).
  aio.begin();

  Serial.println(F("Ready!"));
}

void loop() {
  // Increment the count value and write it to the feed.
  count += 1;
  // To write a value just call the feed's send function and pass it the value.
  // Send will create the feed on Adafruit IO if it doesn't already exist and
  // then add the value to it.  Send returns a boolean that's true if it works
  // and false if it fails for some reason.
  if (testFeed.send(count)) {
    Serial.print(F("Wrote value to feed: ")); Serial.println(count, DEC);
  }
  else {
    Serial.println(F("Error writing value to feed!"));
  }

  // Now wait 10 seconds and read the current feed value.
  Serial.println(F("Waiting 10 seconds and then reading the feed value."));
  delay(10000);

  // To read the latest feed value call the receive function on the feed.
  // The returned object will be a FeedData instance and you can check if it's
  // valid (i.e. was successfully read) by calling isValid(), and then get the
  // value either as a text value, or converted to an int, float, etc.
  FeedData latest = testFeed.receive();
  if (latest.isValid()) {
    Serial.print(F("Received value from feed: ")); Serial.println(latest);
    // By default the received feed data item has a string value, however you
    // can use the following functions to attempt to convert it to a numeric
    // value like an int or float.  Each function returns a boolean that indicates
    // if the conversion succeeded, and takes as a parameter by reference the
    // output value.
    int i;
    if (latest.intValue(&i)) {
      Serial.print(F("Value as an int: ")); Serial.println(i, DEC);
    }
    // Other functions that you can use include:
    //  latest.uintValue() (unsigned int)
    //  latest.longValue() (long)
    //  latest.ulongValue() (unsigned long)
    //  latest.floatValue() (float)
    //  latest.doubleValue() (double)
  }
  else {
    Serial.print(F("Failed to receive the latest feed value!"));
  }

  // Now wait 10 more seconds and repeat.
  Serial.println(F("Waiting 10 seconds and then writing a new feed value."));
  delay(10000);
}

/**************************************************************************/
/*!
    @brief  Tries to read the CC3000's internal firmware patch ID
*/
/**************************************************************************/
uint16_t checkFirmwareVersion(void)
{
  uint8_t major, minor;
  uint16_t version;
  
  if(!cc3000.getFirmwareVersion(&major, &minor))
  {
    Serial.println(F("Unable to retrieve the firmware version!\r\n"));
    version = 0;
  }
  else
  {
    Serial.print(F("Firmware V. : "));
    Serial.print(major); Serial.print(F(".")); Serial.println(minor);
    version = major; version <<= 8; version |= minor;
  }
  return version;
}
