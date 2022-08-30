/* Adafruit IO Example Using WiFiManager with Custom Adafruit IO parameters
 *
 * This is a simple Adafruit feed subscribe example that uses
 * WiFiManager to handle setup of WiFi credentials and connecting
 * to the network instead of defining the WiFI SSID and password
 * explicitly in the code.
 *
 * In addition, this example allows you to enter your Adafruit IO username and key
 * as customer parameters in WiFiManager so that they do not need to be coded into
 * the sketch.
 * 
 * This is useful if you want to create projects and share them with others that
 * may use them on a different WiFi network and use a different Adafruit IO account
 * for IOT integrations such as collecting sensor data or voice command integration via
 * IFFT.
 *
 * To use this example, setup a feed called "myfeed".  When the ESP8266 or ESP32
 * microcontroller starts, join the "WiFi Setup" SSID and you should be presented
 * with the config portal.  If the config portal does not automatically start you
 * can browse to http://192.168.4.1 to access it
 *
 * Select the SSID and enter the password for WiFi Access in the config portal.
 * Enter your Adafruit IO username and key in the config portal and select "Save".
 *
 * When you manually add data to the feed on io.adafruit.com, you'll see
 * that data written to the serial output.
 *
 * Brad Black - 2022
 *
 */

#include <WiFiManager.h>
#include "AdafruitIO_WiFi.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

char IO_USERNAME[64] = "";
char IO_KEY[64] = "";

static uint8_t objStorage[sizeof(AdafruitIO_WiFi)]; // RAM for the object
AdafruitIO_WiFi *io;                                // a pointer to the object, once it's constructed

// create WiFiManager object and define our custom parameters

WiFiManager wifiManager;
WiFiManagerParameter custom_IO_USERNAME("iouser", "Adafruit IO Username", IO_USERNAME, 60);
WiFiManagerParameter custom_IO_KEY("iokey", "Adafruit IO Key", IO_KEY, 60);

void handleMessage(AdafruitIO_Data *data)
{

  Serial.print("received <- ");
  Serial.println(data->toString());

} // handleMessage

// callback notifying us of the need to save config
void saveConfigCallback()
{

  Serial.println("Saving new config");

  strcpy(IO_USERNAME, custom_IO_USERNAME.getValue());
  strcpy(IO_KEY, custom_IO_KEY.getValue());

  DynamicJsonDocument json(256);

  json["IO_KEY"] = IO_KEY;
  json["IO_USERNAME"] = IO_USERNAME;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile)
  {
    Serial.println("Failed to open config file for writing");
  }

  serializeJson(json, Serial);

  serializeJson(json, configFile);

  configFile.close();
} // end save

void readParamsFromFS()
{
  if (LittleFS.begin())
  {

    if (LittleFS.exists("/config.json"))
    {
      // file exists, reading and loading
      Serial.println("Reading config file");

      File configFile = LittleFS.open("/config.json", "r");
      if (configFile)
      {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(256);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        Serial.println();
        if (!deserializeError)
        {

          if (json.containsKey("IO_USERNAME"))
            strcpy(IO_USERNAME, json["IO_USERNAME"]);
          if (json.containsKey("IO_KEY"))
            strcpy(IO_KEY, json["IO_KEY"]);
        }
        else
        {
          Serial.println("Failed to load json config");
        }
        configFile.close();
      }
    }

    else
    {
      Serial.println("Failed to mount FS");
    }
  }
}
void setup()

{
  Serial.begin(115200); // Initialize serial port for debugging.
  delay(500);
  WiFi.begin();

  readParamsFromFS(); // get parameters from file system

  //wifiManager.resetSettings();  //uncomment to reset the WiFi settings

  wifiManager.setClass("invert");          // enable "dark mode" for the config portal
  wifiManager.setConfigPortalTimeout(120); // auto close configportal after n seconds
  wifiManager.setAPClientCheck(true);      // avoid timeout if client connected to softap

  wifiManager.addParameter(&custom_IO_USERNAME); // set custom paraeter for IO username
  wifiManager.addParameter(&custom_IO_KEY);      // set custom parameter for IO key

  custom_IO_KEY.setValue(IO_KEY, 64);           // set custom parameter value
  custom_IO_USERNAME.setValue(IO_USERNAME, 64); // set custom parameter value

  wifiManager.setSaveConfigCallback(saveConfigCallback); // set config save notify callback

  if (!wifiManager.autoConnect("WiFi Setup")) // connect to wifi with existing setting or start config
  {
    Serial.println("Failed to connect and hit timeout");
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("Connected to WiFi.");

    // connect to Adafruit IO

    io = new (objStorage) AdafruitIO_WiFi(IO_USERNAME, IO_KEY, "", "");

    Serial.printf("Connecting to Adafruit IO with User: %s Key: %s.\n", IO_USERNAME, IO_KEY);

    io->connect();

    AdafruitIO_Feed *myfeed = io->feed("myfeed");

    myfeed->onMessage(handleMessage);

    myfeed->get();

    // wait for a connection

    while ((io->status() < AIO_CONNECTED))
    {
      Serial.print(".");
      delay(500);
    }
    Serial.println("Connected to Adafruit IO.");
  }

} // setup()

void loop()
{

  io->run();

} // loop()
