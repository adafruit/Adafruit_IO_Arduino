/* Adafruit IO Example Using WiFiManager
 *
 * This is a simple Adafruit feed subscribe example that uses
 * WiFiManager to handle setup of WiFi credentials and connecting
 * to the network instead of defining the WiFI SSID and password
 * explicitly in the code.
 *
 * To use this example, add your Adafruit IO Username and Key
 * and setup a feed called "myfeed".  When you manually add data
 * to the feed on io.adafruit.com, you'll see that data written to
 * the serial output.
 *
 * Brad Black - 2022
 *
 */

#include <WiFiManager.h>
#include "AdafruitIO_WiFi.h"

char IO_USERNAME[64] = "my username";
char IO_KEY[64] = "my key";
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, "", "");
AdafruitIO_Feed *myfeed = io.feed("myfeed");

WiFiManager wifiManager;

void handleMessage(AdafruitIO_Data *data)
{

  Serial.print("received <- ");
  Serial.println(data->toString());

} // handleMessage

void setup()

{
  Serial.begin(115200); // Initialize serial port for debugging.
  delay(500);

  // wifiManager.resetSettings();  //uncomment to reset the WiFi settings

  wifiManager.setClass("invert");          // enable "dark mode" for the config portal
  wifiManager.setConfigPortalTimeout(120); // auto close configportal after n seconds
  wifiManager.setAPClientCheck(true);      // avoid timeout if client connected to softap

  if (!wifiManager.autoConnect("WiFi Setup"))   // connect to wifi with existing setting or start config
  {
    Serial.println("failed to connect and hit timeout");
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("Connected to WiFi.");

    Serial.printf("Connecting to Adafruit IO with User: %s Key: %s.\n", IO_USERNAME, IO_KEY);
    io.connect();

    myfeed->onMessage(handleMessage);

    myfeed->get();

    // wait for a connection

    while ((io.status() < AIO_CONNECTED))
    {
      Serial.print(".");
      delay(500);
    }
    Serial.println("Connected to Adafruit IO.");
  }

} // setup()

void loop()
{

  io.run();

} // loop()
