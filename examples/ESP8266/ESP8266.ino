#include "AdafruitIO_ESP8266.h"

/************************* WiFi Access Point *********************************/

#define WIFI_SSID       "your_ssid"
#define WIFI_PASS       "your_pass"

/*************************** Adafruit IO Setup *******************************/

#define IO_USERNAME    "your_username"
#define IO_KEY         "your_key"

/*************************** Global State ************************************/

// Setup the IO client
AdafruitIO_ESP8266 io(WIFI_SSID, WIFI_PASS);

void setup() {

  Serial.begin(115200);
  delay(10);

  Serial.print("Connecting to Adafruit IO");
  delay(1000);

  io.connect(IO_USERNAME, IO_KEY);

}

void loop() {

}
