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

// feed init
AdafruitIO_Feed *foo = io.feed("foo");
AdafruitIO_Feed *bar = io.feed("bar");

void setup() {

  Serial.begin(115200);
  Serial.println(F("Connecting to Adafruit IO"));

  // connect to io.adafruit.com
  io.connect(IO_USERNAME, IO_KEY);

  // setup error handler
  io.setErrorHandler(onError);

  // setup feed callbacks
  foo->onMessage(handleFoo);
  bar->onMessage(handleBar);

  // wait for connection
  while(io.status() != AIO_CONNECTED) {
    Serial.print(F("."));
    delay(500);
  }
  Serial.println(io.statusText());

}

void loop() {
  io.run();
}

void onError(char* err, uint16_t len) {
  Serial.print("ERROR: ");
  Serial.println(err);
}

void handleFoo(char* err, uint16_t len) {
  Serial.print("foo: ");
  Serial.println(err);
}

void handleBar(char* err, uint16_t len) {
  Serial.print("bar: ");
  Serial.println(err);
}
