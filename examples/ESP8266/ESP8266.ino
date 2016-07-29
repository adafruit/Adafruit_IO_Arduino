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

int count = 0;

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

  // save count to the 'foo' feed
  foo->save(count);
  count++;
  delay(1000);

}

void onError(char* err, uint16_t len) {
  Serial.print("ERROR: ");
  Serial.println(err);
}

void handleFoo(AdafruitIO_Data *data) {

  Serial.print("foo: ");

  // you can use isTrue() to check if your feed value
  // is equal to 1, t, true, T, True, or TRUE
  if(data->isTrue())
    Serial.println("is true");
  else
    Serial.println("is false");

}

void handleBar(AdafruitIO_Data *data) {

  // you can get at the parent feed by using data->feed
  Serial.print(data->feed->name);
  Serial.print(": ");

  // value() returns char
  Serial.println(data->value());

  // get double value
  Serial.print("toDouble: ");
  Serial.println(data->toDouble());

  // get int value
  Serial.print("toInt: ");
  Serial.println(data->toInt());

  // get bool value
  Serial.print("toBool: ");
  Serial.println(data->toBool());

  // get location info as double
  Serial.print("bar lat: ");
  Serial.println(data->lat());
  Serial.print("bar lon: ");
  Serial.println(data->lon());
  Serial.print("bar ele: ");
  Serial.println(data->ele());

}
